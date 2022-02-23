#include "Plane.hpp"

Plane::Plane() : pPi(), normal() {

}

Plane::Plane(Point *pPi, Vector pNormal) : pPi(pPi), normal(pNormal) {}

Point* Plane::intersectionLinePlane(const Point &p0, const Vector &vector0) const {
    //t_int = ( (P0 - Ppi) * n ) / (u*n)

    //vector eh o Ppi - P0
    Vector vector = Utils::pointSubtraction(p0, *pPi);
    //product0 eh o resultado do vector * n
    double product0 = Utils::scalarProduct(vector, normal);
    //product1 eh o u*n
    double product1 = Utils::scalarProduct(vector0, normal);

    if(product1 == 0){
        return nullptr;
    }

    //t_int eh o resultado de cima / resultado de baixo
    double t_int = product0/product1;

    //Dado um point p0 e um vector vector0 retornar a equacao da reta (P(t) = Po + t * V)
    return Utils::lineEquation(p0, t_int, vector0);
}