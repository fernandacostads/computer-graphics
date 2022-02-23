#ifndef COMPUTACAOGRAFICA_LIGHT_HPP
#define COMPUTACAOGRAFICA_LIGHT_HPP
#include "Utils.hpp"
#include "IntersectionPoint.hpp"
#include "Camera.hpp"

class Light {
public:
    Vector RGBIntensity;
    bool state;
    virtual Vector calculateDifuseIntensity(const IntersectionPoint& p) = 0;
    virtual Vector calculateSpecularIntensity(const IntersectionPoint& p) = 0;
    virtual void changeCoordinateCamera(Camera *camera) = 0;
    virtual void changeCoordinateWorld(Camera *camera) = 0;
    Light(float r, float g, float b);
};


#endif
