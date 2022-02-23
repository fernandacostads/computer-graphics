#ifndef COMPUTACAOGRAFICA_CONE_HPP
#define COMPUTACAOGRAFICA_CONE_HPP
#include "Utils.hpp"
#include "Object_.hpp"
#include "Matrix.hpp"
#include "Plane.hpp"

class Object_;
class Cone : public Object_{
public:
    string name;
    float height;
    float radius;
    Plane* base;
    Point* center;
    Vector normal;

    Cone(float pHeight, float pRadius, Point* pCenter, Vector pNormal, Material* material);
    Vector calculateNormal(Point* pi);
    bool validatePointCone(Point* vertex, Point* pInt);
    tuple<Point*,Object_*> lineIntersection(Point* pP0, const Vector &pV0) override;
    Point* firstIntersection(const Point &pP0, const Vector &pVector0);
    Point* intersectionLineBase(Point* center, const Point& pP0, const Vector &pVector0);
    void changeCoordinateCamera(Camera *camera) override;
    void changeCoordinateWorld(Camera *camera) override;
    void applyTransformation(vector<Matrix> &pTransfMatrixes) override;
    Point* getCenter() override;


    tuple<Point, Point> Limits() override;
};


#endif
