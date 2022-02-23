#include "IntersectionPoint.hpp"
IntersectionPoint::IntersectionPoint(Point* pP, Object_ *pObject, double pOriginDist) : p(pP), object(pObject),
originDist(pOriginDist){}

IntersectionPoint::IntersectionPoint() = default;;