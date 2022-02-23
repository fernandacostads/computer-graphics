#include <cfloat>
#include <cmath>
#include "Cylinder.hpp"
#include "Plane.hpp"
#include "Cluster.h"


Cylinder::Cylinder(float pHeight, float pRadius, Point pCenter, Vector pNormal, Material *m) : height(pHeight),
    radius(pRadius), center(pCenter), normal(pNormal), baseInf(&center, pNormal),
    baseSup(), Object_("Cylinder", false, m) {

    Vector H_n = normal*height;
    centerSup = Point{center.x + H_n.x, center.y + H_n.y, center.z + H_n.z};
    baseSup = Plane(&centerSup, normal);
}

tuple<Point*,Object_*> Cylinder::lineIntersection(Point* pP0, const Vector &pV0){
    Point* p_int1 = firstIntersection(*pP0, pV0);
    return make_tuple(p_int1, this);
}

bool Cylinder::sidePointValidation(const Point &pInt) const {
    Vector PB = Utils::pointSubtraction(center, pInt);
    double PB_u = Utils::scalarProduct(PB, normal);

    return 0 <= PB_u && PB_u <= height;
}

Vector Cylinder::calculateNormal(Point* pi){
    Vector PIMinusCB = Utils::pointSubtraction(center, *pi);
    double aux = Utils::scalarProduct(PIMinusCB, normal);
    Vector aux2 = normal * aux;

    Point pe{center.x + aux2.x, center.y + aux2.y, center.z + aux2.z};
    Vector PIMinusPE = Utils::pointSubtraction(pe, *pi);

    Vector normalToPoint = PIMinusPE / radius;
    return normalToPoint;
};

void Cylinder::changeCoordinateCamera(Camera *camera) {
    camera->changeWorldCamera(&center);
    camera->changeWorldCamera(normal);
    camera->changeWorldCamera(&centerSup);
    camera->changeWorldCamera(baseInf.normal);
    camera->changeWorldCamera(baseSup.normal);
}

void Cylinder::changeCoordinateWorld(Camera *camera) {
    camera->changeCameraWorld(&center);
    camera->changeCameraWorld(normal);
    camera->changeCameraWorld(&centerSup);
    camera->changeCameraWorld(baseInf.normal);
    camera->changeCameraWorld(baseSup.normal);
}

Point *Cylinder::firstIntersection(const Point &pP0, const Vector &pVector0) {
    // A*t_int² + 2B*t_int + C = 0

    // Normalizar o vetor_d
    auto normalVector = Utils::normalizeVector(pVector0);

    // C0P0 eh o P0 - C0
    Vector C0P0 = Utils::pointSubtraction(center, pP0);

    // V eh o ((C0P0) - ((C0P0)* vetor_n)* vetor_n)
    Vector v = C0P0 - (normal * Utils::scalarProduct(C0P0, normal));

    // W eh o (pVector0 - (pVector0 * vetor_n)*vetor_n)
    Vector w = normalVector - (normal * Utils::scalarProduct(normalVector,normal));

    //A = w*w
    double a = Utils::scalarProduct(w,w);

    //B = (v*w)
    double b = Utils::scalarProduct(v,w);

    //C = (v*v - R²)
    double c = Utils::scalarProduct(v,v) - (radius*radius);

    //delta
    double delta = b*b - a*c;
    /*  Δ > 0 has 2 intersections
         Δ = 0 has 1 intersections
         Δ < 0 has 0 intersections */

    if(delta < 0) return nullptr;

    double t_int1,t_int2;
    auto shorterDistance = DBL_MAX;

    // Intersecao with the base
    Point* p_int1 = baseInf.intersectionLinePlane(pP0,pVector0);
    if(p_int1) {
        if(Utils::distanceBetweenPoints(*p_int1, center) > radius){
            p_int1 = nullptr;
        } else {
            shorterDistance = Utils::distanceBetweenPoints(pP0, *p_int1);
        }
    }

    // Intersecao with the top
    Point* p_int2 = baseSup.intersectionLinePlane(pP0,pVector0);
    if(p_int2 && Utils::distanceBetweenPoints(*p_int2, centerSup) <= radius) {
        double dist2 = Utils::distanceBetweenPoints(*p_int2, pP0);
        if(!p_int1 || dist2 < shorterDistance) {
            p_int1 = p_int2;
            shorterDistance = dist2;
        }
    }

    // Intersecao with the side
    t_int1 = (-b + sqrt(delta))/a;
    t_int2 = (-b - sqrt(delta))/a;

    Point* pTest1 = Utils::lineEquation(pP0, t_int1, normalVector);
    Point* pTest2 = Utils::lineEquation(pP0, t_int2, normalVector);


    if (sidePointValidation(*pTest1)){
        double dist1 = Utils::distanceBetweenPoints(*pTest1, pP0);
        if(dist1 < shorterDistance) {
            p_int1 = pTest1;
            shorterDistance = dist1;
        }
    }
    if (sidePointValidation(*pTest2)) {
        double dist2 = Utils::distanceBetweenPoints(*pTest2, pP0);
        if(dist2 < shorterDistance) {
            p_int1 = pTest2;
        }
    }

    return p_int1;
}


Point *Cylinder::getCenter() {
    return &center;
}

void Cylinder::applyTransformation(vector<Matrix> &pTransfMatrixes) {
    Matrix centerAux = Matrix(4,1,0);
    centerAux(0,0) = center.x;
    centerAux(1,0) = center.y;
    centerAux(2,0) = center.z;
    centerAux(3,0) = 1;
    Matrix centerSupAux = Matrix(4,1,0);
    centerSupAux(0,0) = centerSup.x;
    centerSupAux(1,0) = centerSup.y;
    centerSupAux(2,0) = centerSup.z;
    centerSupAux(3,0) = 1;
    Matrix normalBiSAux = Matrix(4,1,0);
    normalBiSAux(0,0) = baseSup.normal.x;
    normalBiSAux(1,0) = baseSup.normal.y;
    normalBiSAux(2,0) = baseSup.normal.z;
    normalBiSAux(3,0) = 0;
    Matrix normalAux = Matrix(4,1,0);
    normalAux(0,0) = normal.x;
    normalAux(1,0) = normal.y;
    normalAux(2,0) = normal.z;
    normalAux(3,0) = 0;
    for (auto &matrix : pTransfMatrixes) {
        centerAux = matrix * centerAux;
        centerSupAux = matrix * centerSupAux;
        normalBiSAux = matrix * normalBiSAux;
        normalAux = matrix * normalAux;
    }
    center.x = centerAux(0,0);
    center.y = centerAux(1,0);
    center.z = centerAux(2,0);

    centerSup.x = centerSupAux(0,0);
    centerSup.y = centerSupAux(1,0);
    centerSup.z = centerSupAux(2,0);

    normal.x = normalAux(0,0);
    normal.y = normalAux(1,0);
    normal.z = normalAux(2,0);
    baseInf.normal = normal;

    baseSup.normal.x = normalBiSAux(0,0);
    baseSup.normal.y = normalBiSAux(1,0);
    baseSup.normal.z = normalBiSAux(2,0);
}

tuple<Point, Point> Cylinder::Limits()
{
    Point max = center + (normal * height);
    Point min = center + (normal * height);
    Vector prod(1, 0, 0);
    if(normal.y != 1) {
        prod = Utils::vectorProduct(normal, Vector(0, 1, 0));
    }
    Vector prod2 = Utils::vectorProduct(prod, normal);
    for(int i = 0; i < 4; i ++) {
        Point pBase = center + (prod * radius) + (prod2 * radius);
        if(pBase.x > max.x){
            max.x = pBase.x;
        }
        if(pBase.y > max.y){
            max.y = pBase.y;
        }
        if(pBase.z > max.z){
            max.z = pBase.z;
        }
        if(pBase.x < min.x){
            min.x = pBase.x;
        }
        if(pBase.y < min.y){
            min.y = pBase.y;
        }
        if(pBase.z < min.z){
            min.z = pBase.z;
        }
        Point pTop = pBase + (normal * height);
        if(pTop.x > max.x){
            max.x = pBase.x;
        }
        if(pTop.y > max.y){
            max.y = pBase.y;
        }
        if(pTop.z > max.z){
            max.z = pBase.z;
        }
        if(pTop.x < min.x){
            min.x = pBase.x;
        }
        if(pTop.y < min.y){
            min.y = pBase.y;
        }
        if(pTop.z < min.z){
            min.z = pBase.z;
        }
        prod = prod2;
        prod2 = Utils::vectorProduct(prod, normal);
    }
    return make_tuple(max, min);
}
