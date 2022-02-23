#include "Camera.hpp"

Camera::Camera(Point *pCoordCamera, Point *pLookAt, Point *pViewUp, double gridSize, double distGrid, int pNumberOfHoles) :
cameraCoord(pCoordCamera), lookAt(pLookAt), viewUp(pViewUp), numberOfHoles(pNumberOfHoles) {
    observer = Utils::createPoint(0,0,0);
    kc = Utils::normalizeVector(Utils::pointSubtraction(*lookAt, *cameraCoord));
    ic = Utils::normalizeVector(Utils::vectorProduct(
        Utils::pointSubtraction(*cameraCoord, *viewUp),kc));
    jc = Utils::vectorProduct(kc,ic);
    buildCoordMatrix();

    double pointDistance = gridSize/(numberOfHoles);
    double xPos;
    double yPos;
    double z = distGrid;

    cameraGrid = Utils::MatrixAllocation(numberOfHoles);
    for(int column = 0; column < numberOfHoles; ++column ){
        xPos = gridSize/2 - pointDistance - column*pointDistance;
        for (int row = 0; row < numberOfHoles; ++row){
            yPos = -gridSize/2 + pointDistance + row*pointDistance;

            Point *p = Utils::createPoint(xPos,yPos,z);

            cameraGrid[row][column] = p;
        }
    }
}

void Camera::buildCoordMatrix() {
    cameraWorld[0][0] = ic.x;
    cameraWorld[0][2] = kc.x;
    cameraWorld[0][1] = jc.x;
    cameraWorld[0][3] = cameraCoord->x;

    cameraWorld[1][0] = ic.y;
    cameraWorld[1][1] = jc.y;
    cameraWorld[1][2] = kc.y;
    cameraWorld[1][3] = cameraCoord->y;

    cameraWorld[2][0] = ic.z;
    cameraWorld[2][1] = jc.z;
    cameraWorld[2][2] = kc.z;
    cameraWorld[2][3] = cameraCoord->z;

    cameraWorld[3][0] = 0;
    cameraWorld[3][1] = 0;
    cameraWorld[3][2] = 0;
    cameraWorld[3][3] = 1;


    worldCamera[0][0] = ic.x;
    worldCamera[0][1] = ic.y;
    worldCamera[0][2] = ic.z;
    worldCamera[0][3] = - Utils::scalarProduct(*cameraCoord, ic);

    worldCamera[1][0] = jc.x;
    worldCamera[1][1] = jc.y;
    worldCamera[1][2] = jc.z;
    worldCamera[1][3] = - Utils::scalarProduct(*cameraCoord, jc);

    worldCamera[2][0] = kc.x;
    worldCamera[2][1] = kc.y;
    worldCamera[2][2] = kc.z;
    worldCamera[2][3] = - Utils::scalarProduct(*cameraCoord, kc);

    worldCamera[3][0] = 0;
    worldCamera[3][1] = 0;
    worldCamera[3][2] = 0;
    worldCamera[3][3] = 1;
}

template<std::size_t S>
void matrixMult(const double matrix [S][S], const double vector [S], double (&result)[S]) {
    for (int i = 0; i < S ; ++i) {
        result[i] = 0;
        for (int j = 0; j < S; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void Camera::updateCamera(){
    kc = Utils::normalizeVector(Utils::pointSubtraction(*lookAt, *cameraCoord));
    ic = Utils::normalizeVector(Utils::vectorProduct(
        Utils::pointSubtraction(*cameraCoord,*viewUp), kc));
    jc = Utils::vectorProduct(kc,ic);
    buildCoordMatrix();
}

void Camera::changeWorldCamera(Point *point) {
    double result[4];
    double aux[4] = {point->x, point->y, point->z, 1};
    matrixMult<4>(worldCamera, aux, result);
    point->x = result[0];
    point->y = result[1];
    point->z = result[2];
}

void Camera::changeWorldCamera(Vector &v) {
    double result[4];
    double extVector[4] = {v.x, v.y, v.z, 0};
    matrixMult<4>(worldCamera, extVector, result);
    v.x = result[0];
    v.y = result[1];
    v.z = result[2];
}

void Camera::changeCameraWorld(Point *point) {
    double result[4];
    double aux[4] = {point->x, point->y, point->z, 1};
    matrixMult<4>(cameraWorld,aux, result);
    point->x = result[0];
    point->y = result[1];
    point->z = result[2];
}

void Camera::changeCameraWorld(Vector &vector) {
    double result[4];
    double extVector[4] = {vector.x, vector.y, vector.z, 0};
    matrixMult<4>(cameraWorld, extVector, result);
    vector.x = result[0];
    vector.y = result[1];
    vector.z = result[2];
}

void Camera::moveForwads() {
    cameraCoord = Utils::lineEquation(*cameraCoord, 3,
            Utils::normalizeVector(Utils::pointSubtraction(*cameraCoord, *lookAt)));
    updateCamera();
}

void Camera::moveBackwards() {
    cameraCoord = Utils::lineEquation(*cameraCoord, -3,
            Utils::normalizeVector(Utils::pointSubtraction(*cameraCoord, *lookAt)));
    updateCamera();
}

