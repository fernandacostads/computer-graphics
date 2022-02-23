#ifndef COMPUTACAOGRAFICA_INTERSECTIONPOINT_HPP
#define COMPUTACAOGRAFICA_INTERSECTIONPOINT_HPP
#include "Utils.hpp"
#include "Object_.hpp"

class IntersectionPoint {
public:
    Point *p;
    Object_ *object;
    double originDist;
    IntersectionPoint(Point* pP, Object_ *pObject, double originDist);
    IntersectionPoint();
};


#endif
