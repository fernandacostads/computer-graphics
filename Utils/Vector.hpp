#ifndef COMPUTACAOGRAFICA_VECTOR_H
#define COMPUTACAOGRAFICA_VECTOR_H


#include "Utils.hpp"

struct Point{
    double x;
    double y;
    double z;
};

class Vector {
public:
    Vector();
    Vector(double pX, double pY, double pZ);

    double x;
    double y;
    double z;

    Vector operator-() {
        return Vector{-x, -y, -z};
    }

    void operator+=(const Vector &v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
};

inline Vector operator/(const Vector& dividend, const double &divisor) {
    return Vector{dividend.x/divisor, dividend.y/divisor, dividend.z/divisor};
}

inline Vector operator-(const Point &p1, const Point &p2) {
    return Vector(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z);
}

inline Vector operator-(const Vector &v1, const Vector &v2) {
    return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector operator+(const Vector &v1, const Vector &v2) {
    return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector operator*(const Vector &v1, const double &mult) {
    return Vector{v1.x * mult, v1.y * mult, v1.z * mult};
}

inline Vector operator*( const double &mult, const Vector &v1) {
    return v1 * mult;
}

inline Point operator+(const Point &p, const Vector &v) {
    return Point{p.x + v.x, p.y + v.y, p.z + v.z};
}

#endif
