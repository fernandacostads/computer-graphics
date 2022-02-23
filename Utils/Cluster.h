#ifndef COMPUTACAOGRAFICA_CLUSTER_H
#define COMPUTACAOGRAFICA_CLUSTER_H


#include "Object_.hpp"

class Cluster
    : public Object_
{
private:
    vector<Object_ *> _internalObjects;
    Object_ * _collision;
public:
    Cluster(Object_* collision);
    void addObject(Object_ * obj);
    tuple<Point*,Object_*> lineIntersection(Point* pP0, const Vector &pV0) override;
    Point* firstIntersection(const Point &pP0, const Vector &pVector0) override;
    void applyTransformation(vector<Matrix> &pTransfMatrixes) override;
    void changeCoordinateCamera(Camera *camera) override;
    void changeCoordinateWorld(Camera *camera) override;
    Vector calculateNormal(Point* p) override;
    Point* getCenter() override;
    tuple<Point, Point> Limits() override;
};


#endif
