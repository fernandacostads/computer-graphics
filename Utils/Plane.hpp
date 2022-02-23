#ifndef COMPUTACAOGRAFICA_PLANE_HPP
#define COMPUTACAOGRAFICA_PLANE_HPP
#include "Utils.hpp"

class Plane {
public:
    Point *pPi;
    Vector normal;

    Plane();
    Plane(Point *pPi, Vector pNormal);
    Point* intersectionLinePlane(const Point &p0, const Vector &vector0) const;
};


#endif
