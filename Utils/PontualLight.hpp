#ifndef COMPUTACAOGRAFICA_LUZPONTUAL_HPP
#define COMPUTACAOGRAFICA_LUZPONTUAL_HPP


#include "Light.hpp"
#include "Utils.hpp"
#include "IntersectionPoint.hpp"

class PontualLight : public Light {
public:
    Point* currentPosition;
    PontualLight(float r, float g, float b, double x,double y,double z);
    double calculateDifuseFactor(const IntersectionPoint& p);
    Vector calculateDifuseIntensity(const IntersectionPoint& p) override;
    Vector calculateSpecularIntensity(const IntersectionPoint& p) override;
    double calculateSpecularFactor(const IntersectionPoint& p);
    void changeCoordinateCamera(Camera *camera);
    void changeCoordinateWorld(Camera *camera);
};


#endif 
