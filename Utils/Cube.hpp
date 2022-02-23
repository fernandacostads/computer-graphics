#ifndef COMPUTACAOGRAFICA_CUBE_HPP
#define COMPUTACAOGRAFICA_CUBE_HPP
#include "Utils.hpp"
#include "Object_.hpp"
#include "Plane.hpp"
#include "Triangle.hpp"
#include <vector>

struct Vertex {
    string id;
    Point* p;
};

struct Edge{
    string id;
    Vertex* initialVertex;
    Vertex* finalVertex;
};

class Triangle;

struct Face {
    Triangle* t1;
    Triangle* t2;
};
class Cube : public Object_ {
public:
    double edge;
    Point* center;
    vector<Triangle*> triangles;
    vector<Vertex*> vertices;
    vector<Face*> faces;
    vector<Edge*> edges;
    Vector normal;
    Vertex* closerVertex;

    Cube(double cEdge, Point* cCenter, Material* material);
    tuple<Point*,Object_*> lineIntersection(Point* pP0, const Vector &pV0) override;
    Point* firstIntersection(const Point &pP0, const Vector &pVector0) override;
    Vertex* createVertex(Point* p1,const string& id);
    Face* createFace(Triangle* pT1, Triangle* pT2);
    Edge* createEdge(Vertex* pi, Vertex* pf, const string& id);
    Triangle* createTriangle(Vertex *v1, Vertex *v2, Vertex *v3, const string& id);
    void closestVObs();
    void applyTransformation(vector<Matrix> &pTransfMatrixes) override;

    void changeCoordinateCamera(Camera *camera) override;
    void changeCoordinateWorld(Camera *camera) override;
    Vector calculateNormal(Point* p) override;
    Point* getCenter() override;
    tuple<Point, Point> Limits() override;
};
#endif
