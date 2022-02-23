#ifndef COMPUTACAOGRAFICA_CYLINDER_HPP
#define COMPUTACAOGRAFICA_CYLINDER_HPP
#include "Utils.hpp"
#include "Object_.hpp"
#include "IntersectionPoint.hpp"
#include "Plane.hpp"

class Cylinder : public Object_{
public:
    string name;
    float height;
    float radius;
    Point center;
    Point centerSup;
    Plane baseInf;
    Plane baseSup;
    Vector normal;
    Cylinder(float pHeight, float pRadius, Point pCenter, Vector pNormal, Material *m);
    tuple<Point*,Object_*> lineIntersection(Point* pP0, const Vector &pV0) override;
    Point* firstIntersection(const Point &pP0, const Vector &pVector0) override;
    bool sidePointValidation(const Point &pInt) const;
    void changeCoordinateCamera(Camera *camera) override;
    void changeCoordinateWorld(Camera *camera) override;
    Vector calculateNormal(Point* pi);
    void applyTransformation(vector<Matrix> &pTransfMatrixes) override;
    Point* getCenter() override;

    tuple<Point, Point> Limits() override;
};


#endif
