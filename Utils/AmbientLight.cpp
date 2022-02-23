#include "AmbientLight.hpp"

AmbientLight::AmbientLight(float r, float g, float b){
    RGBIntensity = Vector(r, g, b);
}

Vector AmbientLight::calculateAmbientIntensity(const IntersectionPoint& p){
    Vector Ia;
    Ia.x = RGBIntensity.x * p.object->material->Ka[0];
    Ia.y = RGBIntensity.y * p.object->material->Ka[1];
    Ia.z = RGBIntensity.z * p.object->material->Ka[2];
    return Ia;
}