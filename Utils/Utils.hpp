#ifndef Utils_H
#define Utils_H
#include <iostream>
#include <string>
#include <tuple>
#include "Vector.hpp"

using namespace std;

class Vector;
struct Point;

class Utils{
    public:
        static double scalarProduct(const Vector &v1, const Vector &v2);
        static double scalarProduct(const Point &v1, const Vector &v2);
        static Vector vectorProduct(const Vector &v1, const Vector &v2);
        static Vector normalizeVector(const Vector &vector);
        static Vector findNormal(const Vector &vetor1, const Vector &vetor2);
        static Point* lineEquation(const Point &p, const double &t, const Vector &vector);
        static Point* createPoint(double x, double y, double z);
        static double distanceBetweenPoints(Point* p1, Point* p2);
        static double distanceBetweenPoints(const Point &p1, const Point &p2);
        static Vector pointSubtraction(const Point &p1, const Point &p2);
        static Point*** MatrixAllocation(int size);
        static bool distancePointPlane(Vector &pNormal, Point &pPi, Point &pObj);

    static tuple<Point*, Point*> pointsDistanceData(Point* pOrigin, const Vector &v1, const Vector &v2,
                                                     double lLength);

};

#endif