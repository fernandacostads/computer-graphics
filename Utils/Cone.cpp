#include <cmath>
#include "Cone.hpp"
#include "Plane.hpp"
#include "Cluster.h"


Cone::Cone(float pHeight, float pRadius, Point* pCenter, Vector pNormal, Material *material) : height(pHeight), radius(pRadius),
                                                                          center(pCenter), normal(pNormal),
                                                                           Object_("Cone", false, material) {
    base = new Plane(center, normal);
}

tuple<Point*, Object_*> Cone::lineIntersection(Point* pP0, const Vector &pV0) {

    return make_pair(firstIntersection(*pP0, pV0), this);
}

bool Cone::validatePointCone(Point* vertex, Point* pInt){

    Vector auxVectorTreatment(vertex->x - pInt->x, vertex->y - pInt->y, vertex->z - pInt->z);

    double scalarTreatment = Utils::scalarProduct(auxVectorTreatment,this->normal);
    
    bool treatmentInt = false;
    if(scalarTreatment < 0.00000000001 && scalarTreatment > 0.00000000001)
        scalarTreatment = 0;
    if(scalarTreatment >= 0 && scalarTreatment <= this->height){
        treatmentInt = true;
    }

    return treatmentInt;
}

Point* Cone::intersectionLineBase(Point* center, const Point& pP0, const Vector &pVector0){
    Point* pInt = base->intersectionLinePlane(pP0, pVector0);
    return Utils::distanceBetweenPoints(pInt,center) <= radius? pInt : nullptr;
}

void Cone::changeCoordinateCamera(Camera *camera) {
    camera->changeWorldCamera(center);
    camera->changeWorldCamera(normal);
    camera->changeWorldCamera(base->normal);
}

void Cone::changeCoordinateWorld(Camera *camera) {
    camera->changeCameraWorld(center);
    camera->changeCameraWorld(normal);
    camera->changeCameraWorld(base->normal);
}

Vector Cone::calculateNormal(Point* pi) {

    Vector auxVector = normal*height;

    Point* Vertex = new Point{center->x + auxVector.x, center->y + auxVector.y,
                                           center->z + auxVector.z};

    Vector PIMinusCB = Utils::pointSubtraction(*center, *pi);

    double aux = Utils::scalarProduct(PIMinusCB, normal);
    Point* pe = Utils::lineEquation(*center, aux, normal);


    Vector PIMinusPE = Utils::pointSubtraction(*pe, *pi);
    Vector PiV = Utils::pointSubtraction(*pi, *Vertex);

    Vector T = Utils::vectorProduct(PiV, PIMinusPE);
    Vector N = Utils::vectorProduct(T, PiV);

    delete pe;
    delete Vertex;
    return Utils::normalizeVector(N);
}

Point *Cone::firstIntersection(const Point &pP0, const Vector &pVector0) {
    // aux Vector to calculate cone vertex (H*n)
    Vector auxVector = normal * height;

    Point* vertex = Utils::createPoint(this->center->x + auxVector.x, this->center->y + auxVector.y,
        this->center->z + auxVector.z);

    //vector d normalized
    Vector d = Utils::normalizeVector(pVector0);

    //cos alpha
    double cosAlpha = this->height / (sqrt(pow(this->height,2) + pow(radius,2)));

    //vector v
    Vector v(vertex->x - pP0.x, vertex->y - pP0.y, vertex->z - pP0.z);

    //a
    double a = pow(Utils::scalarProduct(d,this->normal),2) - (Utils::scalarProduct(d,d)*pow(cosAlpha,2));

    //b
    double b = (Utils::scalarProduct(v,d) * pow(cosAlpha,2))
        - (Utils::scalarProduct(v,this->normal))
        * (Utils::scalarProduct(d,this->normal));

    //c
    double c = pow(Utils::scalarProduct(v,this->normal),2)
        - (Utils::scalarProduct(v,v)*pow(cosAlpha,2));

    //delta
    double delta = b*b - a*c;

    if (delta < 0.00000000001 && delta >-0.00000000001 )
        delta = 0;
    if (a < 0.00000000001 && a>-0.00000000001)
        a = 0;
    if (b < 0.00000000001 && b>-0.00000000001)
        b = 0;
    if (c < 0.00000000001 && c>-0.00000000001)
        c = 0;

    /*  Δ > 0 has 2 intersections
        Δ = 0 has 1 intersections
        Δ < 0 has 0 intersections */

    double t_int1,t_int2;
    Point* p_int1 = nullptr;
    bool treatmentInt1 = false, treatmentInt2 = false;

    if (delta > 0){
        if(a!=0){
            t_int1 = (-b + sqrt(delta))/a;
            t_int2 = (-b - sqrt(delta))/a;
        }else{
            t_int1 = -c / 2*b;
            t_int2 = -c / 2*b;
        }

        Point* pTest1 = Utils::lineEquation(pP0,t_int1,d);
        Point* pTest2 = Utils::lineEquation(pP0,t_int2,d);
        treatmentInt1 = this->validatePointCone(vertex,pTest1);
        treatmentInt2 = this->validatePointCone(vertex,pTest2);

        if (treatmentInt1)
            p_int1 = pTest1;
        else if((pTest1 = Cone::intersectionLineBase(this->center, pP0, d)) != nullptr)
            p_int1 = pTest1;

        double p_int1_dis = p_int1 != nullptr ? Utils::distanceBetweenPoints(*p_int1, pP0) : 0;

        if (treatmentInt2) {
            if(p_int1 == nullptr || Utils::distanceBetweenPoints(*pTest2, pP0) < p_int1_dis) {
                p_int1 = pTest2;
            }
        }
        else if((pTest2 = Cone::intersectionLineBase(this->center, pP0, d)) != nullptr &&
            Utils::distanceBetweenPoints(*pTest2, pP0) < p_int1_dis){
            p_int1 = pTest2;
        }

    }
    else if (delta == 0 && (b!=0 && a!=0)){
        t_int1 = (-b + sqrt(delta))/a;
        Point* pTest1 = Utils::lineEquation(pP0,t_int1,d);
        treatmentInt1 = this->validatePointCone(vertex,pTest1);

        if (treatmentInt1)
            p_int1 = pTest1;
        if((pTest1 = Cone::intersectionLineBase(this->center, pP0, d)) != nullptr &&
            (p_int1 == nullptr || Utils::distanceBetweenPoints(*pTest1, pP0) < Utils::distanceBetweenPoints(*p_int1, pP0))) {

            p_int1 = Cone::intersectionLineBase(this->center, pP0, d);
        }

    }

    return p_int1;
}

Point *Cone::getCenter() {
    return center;
}

void Cone::applyTransformation(vector<Matrix> &pTransfMatrixes) {
    Matrix centerAux = Matrix(4,1,0);
    centerAux(0,0) = center->x;
    centerAux(1,0) = center->y;
    centerAux(2,0) = center->z;
    centerAux(3,0) = 1;
    Matrix normalAux = Matrix(4,1,0);
    normalAux(0,0) = normal.x;
    normalAux(1,0) = normal.y;
    normalAux(2,0) = normal.z;
    normalAux(3,0) = 0;
    for (auto &matrix : pTransfMatrixes) {
        centerAux = matrix * centerAux;
        normalAux = matrix * normalAux;
    }
    center->x = centerAux(0,0);
    center->y = centerAux(1,0);
    center->z = centerAux(2,0);

    normal.x = normalAux(0,0);
    normal.y = normalAux(1,0);
    normal.z = normalAux(2,0);
    base->normal = normal;
}

tuple<Point, Point> Cone::Limits()
{
    Point max = *center + (normal * height);
    Point min = *center + (normal * height);
    Vector prod(1, 0, 0);
    if(normal.y != 1) {
        prod = Utils::vectorProduct(normal, Vector(0, 1, 0));
    }
    Vector prod2 = Utils::vectorProduct(prod, normal);
    for(int i = 0; i < 4; i ++) {
        Point pBase = *center + (prod * radius) + (prod2 * radius); 
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
        prod = prod2;
        prod2 = Utils::vectorProduct(prod, normal);
    }
    return make_tuple(max, min);
}

