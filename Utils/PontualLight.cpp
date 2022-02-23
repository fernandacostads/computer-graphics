#include <cmath>
#include "PontualLight.hpp"
#include "Cluster.h"

PontualLight::PontualLight(float r, float g, float b, double x,double y,double z): Light(r, g, b){
    currentPosition = new Point();
    currentPosition->x = x;
    currentPosition->y = y;
    currentPosition->z = z;
}

double PontualLight::calculateDifuseFactor(const IntersectionPoint& p) {
    Vector l = Utils::normalizeVector(Utils::pointSubtraction(*p.p, *currentPosition));
    Vector normal = p.object->calculateNormal(p.p);

    double difuseFactor = Utils::scalarProduct(normal, l);
    if(difuseFactor < 0){
        return 0;
    }
    return difuseFactor;

}

Vector PontualLight::calculateDifuseIntensity(const IntersectionPoint& p){
    Vector Id;
    Id.x = RGBIntensity.x * p.object->material->Kd[0];
    Id.y = RGBIntensity.y * p.object->material->Kd[1];
    Id.z = RGBIntensity.z * p.object->material->Kd[2];

    Id = Id * calculateDifuseFactor(p);
    return Id;
}

void PontualLight::changeCoordinateCamera(Camera *camera) {
    camera->changeWorldCamera(currentPosition);
}

void PontualLight::changeCoordinateWorld(Camera *camera) {
    camera->changeCameraWorld(currentPosition);

}

double PontualLight::calculateSpecularFactor(const IntersectionPoint& p) {
    Vector PlPint = Utils::pointSubtraction(*p.p, *currentPosition);
    Vector l = Utils::normalizeVector(PlPint);

    Vector normal = p.object->calculateNormal(p.p);

    Vector r = ((Utils::scalarProduct(l, normal)) * 2 * normal) - l;
    Vector v = Utils::pointSubtraction(*p.p, Point{0, 0, 0});

    double specularFactor = Utils::scalarProduct(Utils::normalizeVector(v),
        Utils::normalizeVector(r));

    if(specularFactor < 0){
        return 0;
    }

    return specularFactor;

}

Vector PontualLight::calculateSpecularIntensity(const IntersectionPoint& p) {
    Vector Id;
    Id.x = RGBIntensity.x * p.object->material->Ks[0];
    Id.y = RGBIntensity.y * p.object->material->Ks[1];
    Id.z = RGBIntensity.z * p.object->material->Ks[2];

    Id = Id * pow(calculateSpecularFactor(p), p.object->material->m);
    return Id;
}
