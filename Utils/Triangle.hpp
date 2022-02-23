#ifndef COMPUTACAOGRAFICA_TRIANGLE_HPP
#define COMPUTACAOGRAFICA_TRIANGLE_HPP

#include "Cube.hpp"
#include "Object_.hpp"

struct Vertex;

class Triangle {
public:
    Triangle(const string &pId, Vertex *pP1, Vertex *pP2, Vertex *pP3, Plane *pP);
    string id;
    Vertex *p1;
    Vertex *p2;
    Vertex *p3;
    Plane *p;

    Vector p2p3;
    Vector p3p1;
    Vector p1p2;
    Vector p1p3;

    void changeCoordinateCamera(Camera *camera);
    void changeCoordinateWorld(Camera *camera);
    void applyTransformation(vector<Matrix> &pTransfMatrixes);
    bool validatePointTriangle(const Vector &P1P, const Vector &P2P, const Vector &P3P);
    Point* lineIntersection(Point *pP0, const Vector &pV0);


};


#endif 
