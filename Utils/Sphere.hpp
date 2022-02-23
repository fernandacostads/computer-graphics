#ifndef COMPUTACAOGRAFICA_SPHERE_HPP
#define COMPUTACAOGRAFICA_SPHERE_HPP
#include "Utils.hpp"
#include "Object_.hpp"
class Sphere : public Object_ {
public:
    string name;
    float radius;
    Point* center;
    Sphere(float pRadius, Point* pCenter, Material* material);
    tuple<Point*,Object_*> lineIntersection(Point* pP0, const Vector &pV0) override;
    Point* firstIntersection(const Point &pP0, const Vector &pVector0);
    void changeCoordinateCamera(Camera *camera) override;
    void changeCoordinateWorld(Camera *camera) override;
    Vector calculateNormal(Point* p) override;
    void applyTransformation(vector<Matrix> &pTransfMatrixes) override;
    Point* getCenter() override;
    tuple<Point, Point> Limits() override;
};


#endif
