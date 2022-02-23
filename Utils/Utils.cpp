#include <cmath>
#include "Utils.hpp"

double Utils::scalarProduct(const Vector &v1, const Vector &v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double Utils::scalarProduct(const Point &p, const Vector &v) {
    return p.x * v.x + p.y * v.y + p.z * v.z;
}

Vector Utils::vectorProduct(const Vector &v1, const Vector &v2)
{
    return {v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

Vector Utils::normalizeVector(const Vector &vector) {
    return vector/sqrt(scalarProduct(vector,vector));
}

Vector Utils::findNormal(const Vector &vetor1, const Vector &vetor2){
    Vector normalVector;
    normalVector = vectorProduct(vetor1, vetor2);
    normalVector = normalizeVector(normalVector);
    return normalVector;
}

double Utils::distanceBetweenPoints(Point *p1, Point *p2) {
    return sqrt(pow((p2->x - p1->x),2) + pow((p2->y - p1->y),2) + pow((p2->z - p1->z),2));
}

double Utils::distanceBetweenPoints(const Point &p1, const Point &p2) {
    return sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2) + pow((p2.z - p1.z),2));
}

Vector Utils::pointSubtraction(const Point &p1, const Point &p2) {
    return Vector{p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
}

Point*** Utils::MatrixAllocation(int size){
    auto ***matrix = new Point**[size];

    for (int i = 0; i < size; i++){
        matrix[i] = new Point*[size];
    }
    return matrix;
}

Point* Utils::lineEquation(const Point &p, const double &t,const Vector &vector){
    return new Point{p.x + t * vector.x, p.y + t * vector.y, p.z + t * vector.z};
}

Point* Utils::createPoint(double x, double y, double z) {
    Point* p = new Point;
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}

tuple<Point*, Point*> Utils::pointsDistanceData(Point* pOrigin, const Vector &v1, const Vector &v2,
    double lLength){
    double s, t;
    Point* p1;
    Point* p2;

    s = pow(lLength, 2);
    s = s/((scalarProduct(v2,v2)) -
           (pow(scalarProduct(v1,v2),2)/scalarProduct(v1,v1)));
    s = sqrt(s);

    t = scalarProduct(v1,v2)/scalarProduct(v1,v1);
    t = t * s;

    p1 = lineEquation(*pOrigin, t, v1);
    p2 = lineEquation(*pOrigin, s, v2);

    return make_tuple(p1,p2);

}

bool Utils::distancePointPlane(Vector &pNormal, Point &pPi, Point &pObj) {
    return Utils::scalarProduct(pObj,pNormal) + ((- (pNormal.x*pPi.x) - (pNormal.y*pPi.y) - (pNormal.z*pPi.z))/
           sqrt(pow(pNormal.x,2) + pow(pNormal.y,2) +pow(pNormal.z,2))) > 0;
}

