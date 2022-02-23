#include <cmath>
#include "SpotLight.hpp"

SpotLight::SpotLight(float r, float g, float b, double x, double y, double z, Vector pDir,
        float pAng): direcao(pDir), apertureAngle(pAng), Light(r, g, b){
    position = new Point();
    position->x = x;
    position->y = y;
    position->z = z;
    direcao = Utils::normalizeVector(direcao);
}

double SpotLight::calculateDifuseFactor(const IntersectionPoint& p) {
    Vector l = Utils::normalizeVector(Utils::pointSubtraction(*p.p, *position));
    if(Utils::scalarProduct(-l, direcao) > cos(apertureAngle)){
        return 0 ;
    }
    double difuseFactor = Utils::scalarProduct(l, p.object->calculateNormal(p.p));
    if(difuseFactor < 0){
        return 0;
    }
    return difuseFactor;
}

Vector SpotLight::calculateDifuseIntensity(const IntersectionPoint& p) {
    Vector Id;
    Id.x = RGBIntensity.x * p.object->material->Kd[0];
    Id.y = RGBIntensity.y * p.object->material->Kd[1];
    Id.z = RGBIntensity.z * p.object->material->Kd[2];

    Id = Id * calculateDifuseFactor(p);
    return Id;
}

void SpotLight::changeCoordinateCamera(Camera *camera) {
    camera->changeWorldCamera(direcao);
    camera->changeWorldCamera(position);
}

void SpotLight::changeCoordinateWorld(Camera *camera) {
    camera->changeCameraWorld(direcao);
    camera->changeCameraWorld(position);
}

double SpotLight::calculateSpecularFactor(const IntersectionPoint& p) {
    Vector l = Utils::normalizeVector(Utils::pointSubtraction(*p.p, *position));

    Vector normal = p.object->calculateNormal(p.p);

    Vector r = (2 * ((Utils::scalarProduct(l, normal))*normal)) - l;
    Vector v = Utils::pointSubtraction(*p.p, Point{0,0,0});

    if(Utils::scalarProduct(-l, direcao) > cos(apertureAngle)){
        return 0 ;
    }
    double specularFactor = Utils::scalarProduct(v, r);
    if(specularFactor < 0){
        return 0;
    }
    return specularFactor;

}

Vector SpotLight::calculateSpecularIntensity(const IntersectionPoint& p) {
    Vector Is;
    Is.x = RGBIntensity.x * p.object->material->Ks[0];
    Is.y = RGBIntensity.y * p.object->material->Ks[1];
    Is.z = RGBIntensity.z * p.object->material->Ks[2];

    Is = Is * pow(calculateSpecularFactor(p), p.object->material->m);
    return Is;
}