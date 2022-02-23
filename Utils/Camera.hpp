#ifndef COMPUTACAOGRAFICA_CAMERA_HPP
#define COMPUTACAOGRAFICA_CAMERA_HPP
#include "Utils.hpp"

class Camera {
public:
    Point* cameraCoord;
    Point* lookAt;
    Point* viewUp;
    Point* observer;
    Vector ic;
    Vector jc;
    Vector kc;
    double cameraWorld[4][4];
    double worldCamera[4][4];
    Point*** cameraGrid;
    int numberOfHoles;

    Camera(Point* pCoordCamera, Point* pLookAt, Point* pViewUp, double gridSize, double distGrid, int pNumberOfHoles);
    void buildCoordMatrix();
    void changeWorldCamera(Point *point);
    void changeCameraWorld(Point *point);
    void changeWorldCamera(Vector &v);
    void changeCameraWorld(Vector &vector);
    void updateCamera();
    void moveForwads();
    void moveBackwards();


};


#endif 
