#include <cmath>
#include "Sphere.hpp"
#include "Cluster.h"


Sphere::Sphere(float pRadius, Point* pCenter, Material* material) : radius(pRadius), center(pCenter),
                                              Object_("Sphere",false, material)  {}

tuple<Point*, Object_*> Sphere::lineIntersection(Point* pP0, const Vector &pV0){
    //p_t_int eh o point dado o t_int
    Point* p_t_int1 = nullptr;
    Point* p_t_int2 = nullptr;
    double t_int1, t_int2;

    // A*t_int² + B*t_int + C = 0

    Vector pV0N = Utils::normalizeVector(pV0);

    // C0P0 eh o P0 - C0
    Vector C0P0 = Utils::pointSubtraction(*this->center, *pP0);

    // A = u*u
    double productA = Utils::scalarProduct(pV0N,pV0N);

    // B = 2 * (P0 - C0) * u
    double productB = Utils::scalarProduct(C0P0,pV0N);

    // C = (P0 - C0) * (P0 - C0) - R²
    double productC = Utils::scalarProduct(C0P0,C0P0) - (this->radius*this->radius);

    /*  Δ > 0 has 2 intersections
        Δ = 0 has 1 intersections
        Δ < 0 has 0 intersections */

    double Delta = (productB*productB) - (productA)*(productC);

    if (Delta > 0){

        t_int1 = (-productB + sqrt(Delta))/productA;
        t_int2 = (-productB - sqrt(Delta))/productA;
        p_t_int1 = Utils::lineEquation(*pP0,t_int1,pV0N);
        p_t_int2 = Utils::lineEquation(*pP0,t_int2,pV0N);
        if(Utils::distanceBetweenPoints(p_t_int1,pP0) > Utils::distanceBetweenPoints(p_t_int2,pP0)) {
            p_t_int1 = p_t_int2;
        }
    }

    else if (Delta == 0){

        t_int1 = (-productB + sqrt(Delta))/productA;
        p_t_int1 = Utils::lineEquation(*pP0,t_int1,pV0N);
    }

    return make_tuple(p_t_int1, this);

}

void Sphere::changeCoordinateCamera(Camera *camera) {
    camera->changeWorldCamera(center);
}

void Sphere::changeCoordinateWorld(Camera *camera) {
    camera->changeCameraWorld(center);
}

Vector Sphere::calculateNormal(Point* p){
    Vector v;
    v = Utils::pointSubtraction(*this->center,*p);
    v = Utils::normalizeVector(v);
    return v;
}   

Point *Sphere::firstIntersection(const Point &pP0, const Vector &pVector0) {
    return nullptr;
}


Point *Sphere::getCenter() {
    return center;
}

void Sphere::applyTransformation(vector<Matrix> &pTransfMatrixes) {

}

tuple<Point, Point> Sphere::Limits()
{
    Point max{center->x + radius, center->y + radius, center->z + radius};
    Point min{center->x - radius, center->y - radius, center->z - radius};
    return make_tuple(max, min);
}
