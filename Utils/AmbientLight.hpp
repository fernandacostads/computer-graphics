#ifndef COMPUTACAOGRAFICA_AMBIENTLIGHT_HPP
#define COMPUTACAOGRAFICA_AMBIENTLIGHT_HPP

#include "Light.hpp"
#include "Utils.hpp"
#include "IntersectionPoint.hpp"

class AmbientLight {
public:
    Vector RGBIntensity;
    AmbientLight(float r, float g, float b);
    Vector calculateAmbientIntensity(const IntersectionPoint& p);
};


#endif 
