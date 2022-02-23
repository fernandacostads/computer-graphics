#include "Cluster.h"

Cluster::Cluster(Object_* collision) : _collision(collision), Object_("cluster", false, collision->material){}

void Cluster::addObject(Object_ *obj)
{
    _internalObjects.emplace_back(obj);
}

tuple<Point *, Object_ *> Cluster::lineIntersection(Point *pP0, const Vector &pV0)
{
    auto colPoints = _collision->lineIntersection(pP0, pV0);
    Point* pInt = nullptr;
    Point* pIntNext = nullptr;
    double dist = 0, newDistance;
    Object_* pObj = nullptr;
    Object_* pObjNext = nullptr;
    if(std::get<0>(colPoints) != nullptr) {
        for(auto &obj : _internalObjects) {

            tie(pInt, pObj) = obj->lineIntersection(pP0, pV0);
            if(pInt != nullptr && ((pIntNext == nullptr && (newDistance = Utils::distanceBetweenPoints(pInt, pP0)) > 0) ||
            (dist > (newDistance = Utils::distanceBetweenPoints(pInt, pP0))))) {
                dist = newDistance;
                pIntNext = pInt;
                pObjNext = pObj;
            }
        }

        if (pIntNext != nullptr) {
            return make_pair(pIntNext, pObjNext);
        }
    }
    return make_pair(nullptr, nullptr);
}

Point *Cluster::firstIntersection(const Point &pP0, const Vector &pVector0)
{
    if(_collision->firstIntersection(pP0, pVector0) != nullptr) {
        for(auto &obj : _internalObjects) {
            auto point = obj->firstIntersection(pP0, pVector0);
            if(point != nullptr) {
                return point;
            }
        }
    }
    return nullptr;
}

void Cluster::applyTransformation(vector<Matrix> &pTransfMatrixes)
{
    _collision->applyTransformation(pTransfMatrixes);
    for(auto &obj : _internalObjects) {
        obj->applyTransformation(pTransfMatrixes);
    }
}

void Cluster::changeCoordinateCamera(Camera *camera)
{
    _collision->changeCoordinateCamera(camera);
    for(auto &obj : _internalObjects) {
        obj->changeCoordinateCamera(camera);
    }
}

void Cluster::changeCoordinateWorld(Camera *camera)
{
    _collision->changeCoordinateWorld(camera);
    for(auto &obj : _internalObjects) {
        obj->changeCoordinateWorld(camera);
    }
}

Vector Cluster::calculateNormal(Point *p)
{
    return _collision->calculateNormal(p);
}

Point *Cluster::getCenter()
{
    return _collision->getCenter();
}

tuple<Point, Point> Cluster::Limits()
{
    Point max;
    Point min;
    Point newMax;
    Point newMin;
    tie(max, min) = _internalObjects[0]->Limits();
    for(unsigned int i = 1; i < _internalObjects.size(); i++) {
        tie(newMax, newMin) = _internalObjects[i]->Limits();
        if(newMax.x > max.x){
            max.x = newMax.x;
        }
        if(newMax.y > max.y){
            max.y = newMax.y;
        }
        if(newMax.z > max.z){
            max.z = newMax.z;
        }
        if(newMin.x < min.x){
            min.x = newMin.x;
        }
        if(newMin.y < min.y){
            min.y = newMin.y;
        }
        if(newMin.z < min.z){
            min.z = newMin.z;
        }
    }
    return make_tuple(max, min);
}
