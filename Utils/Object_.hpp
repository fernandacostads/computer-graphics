#ifndef COMPUTACAOGRAFICA_OBJECT_HPP
#define COMPUTACAOGRAFICA_OBJECT_HPP
#include "Utils.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Matrix.hpp"

class Object_ {
public:
    string name;
    bool visibility;
    Material* material;
    Object_(const string& pName, bool visibility, Material* pMat);
    virtual std::tuple<Point*,Object_*> lineIntersection(Point* pP0, const Vector &pV0) = 0;
    virtual Point* firstIntersection(const Point &pP0, const Vector &pVector0) = 0;
    virtual void changeCoordinateCamera(Camera *camera) = 0;
    virtual void changeCoordinateWorld(Camera *camera) = 0;
    virtual Vector calculateNormal(Point* p) = 0;
    virtual void applyTransformation(vector<Matrix> &pTransfMatrixes) = 0;
    virtual Point* getCenter() = 0;
    virtual std::tuple<Point, Point> Limits() = 0;
};


#endif 
