#include "Triangle.hpp"

Triangle::Triangle(const string &pId, Vertex *pP1, Vertex *pP2, Vertex *pP3, Plane *pP) : id(pId), p1(pP1),
                p2(pP2),p3(pP3),p(pP){

    p2p3 = Utils::pointSubtraction(*p2->p, *p3->p);
    p3p1 = Utils::pointSubtraction(*p3->p, *p1->p);
    p1p2 = Utils::pointSubtraction(*p1->p, *p2->p);
    p1p3 = Utils::pointSubtraction(*p1->p, *p3->p);
}

void Triangle::changeCoordinateWorld(Camera *camera) {
    camera->changeWorldCamera(p->normal);
    camera->changeWorldCamera(p2p3);
    camera->changeWorldCamera(p3p1);
    camera->changeWorldCamera(p1p2);
    camera->changeWorldCamera(p1p3);
}

void Triangle::changeCoordinateCamera(Camera *camera) {
    camera->changeCameraWorld(p->normal);
    camera->changeCameraWorld(p2p3);
    camera->changeCameraWorld(p3p1);
    camera->changeCameraWorld(p1p2);
    camera->changeCameraWorld(p1p3);
}

bool Triangle::validatePointTriangle(const Vector &P1P, const Vector &P2P, const Vector &P3P) {
    double validation = Utils::scalarProduct(Utils::vectorProduct(p1p2, P1P),
                                                  Utils::vectorProduct(p1p2, p1p3));
    if(validation < 0){
        return false;
    }

    validation = Utils::scalarProduct(Utils::vectorProduct(p2p3, P2P),
                                                  Utils::vectorProduct(p1p2, p1p3));
    if(validation < 0){
        return false;
    }

    validation = Utils::scalarProduct(Utils::vectorProduct(p3p1, P3P),
                                           Utils::vectorProduct(p1p2, p1p3));

    return validation > 0;
}

Point *Triangle::lineIntersection(Point *pP0, const Vector &pV0) {
    Point *point = p->intersectionLinePlane(*pP0, pV0);
    if (point) {
        Vector p1p = Utils::pointSubtraction(*p1->p, *point);
        Vector p2p = Utils::pointSubtraction(*p2->p, *point);
        Vector p3p = Utils::pointSubtraction(*p3->p, *point);

        if (validatePointTriangle(p1p,p2p,p3p)) {
            return point;
        }
    }
    return nullptr;
}

void Triangle::applyTransformation(vector<Matrix> &pTransfMatrixes) {
    Matrix normalAux = Matrix(4,1,0);
    normalAux(0,0) = p->normal.x; normalAux(1,0) = p->normal.y; normalAux(2,0) = p->normal.z; normalAux(3,0) = 0;
    Matrix p2p3aux = Matrix(4,1,0);
    p2p3aux(0,0) = p2p3.x; p2p3aux(1,0) = p2p3.y; p2p3aux(2,0) = p2p3.z; p2p3aux(3,0) = 0;
    Matrix p3p1aux = Matrix(4,1,0);
    p3p1aux(0,0) = p3p1.x; p3p1aux(1,0) = p3p1.y; p3p1aux(2,0) = p3p1.z; p3p1aux(3,0) = 0;
    Matrix p1p2aux = Matrix(4,1,0);
    p1p2aux(0,0) = p1p2.x; p1p2aux(1,0) = p1p2.y; p1p2aux(2,0) = p1p2.z; p1p2aux(3,0) = 0;
    Matrix p1p3aux = Matrix(4,1,0);
    p1p3aux(0,0) = p1p3.x; p1p3aux(1,0) = p1p3.y; p1p3aux(2,0) = p1p3.z; p1p3aux(3,0) = 0;

    for (auto matrix : pTransfMatrixes) {
        normalAux = matrix * normalAux;
        p2p3aux = matrix * p2p3aux;
        p3p1aux = matrix * p3p1aux;
        p1p2aux = matrix * p1p2aux;
        p1p3aux = matrix * p1p3aux;

    }

    p->normal.x = normalAux(0,0);
    p->normal.y = normalAux(1,0);
    p->normal.z = normalAux(2,0);

    p2p3.x = p2p3aux(0,0);
    p2p3.y = p2p3aux(1,0);
    p2p3.z = p2p3aux(2,0);

    p3p1.x =  p3p1aux(0,0);
    p3p1.y =  p3p1aux(1,0);
    p3p1.z =  p3p1aux(2,0);

    p1p2.x = p1p2aux(0,0);
    p1p2.y = p1p2aux(1,0);
    p1p2.z = p1p2aux(2,0);

    p1p3.x = p1p3aux(0,0);
    p1p3.y = p1p3aux(1,0);
    p1p3.z = p1p3aux(2,0);
}

