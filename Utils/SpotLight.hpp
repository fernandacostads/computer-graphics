#ifndef COMPUTACAOGRAFICA_LUZSPOT_HPP
#define COMPUTACAOGRAFICA_LUZSPOT_HPP

#include "Light.hpp"
#include "IntersectionPoint.hpp"
#include "Object_.hpp"

class SpotLight : public Light{
public:
    Point* position;
    Vector direcao;
    float apertureAngle;
    SpotLight(float r, float g, float b, double x, double y, double z, Vector pDir,
            float pAng);
    double calculateDifuseFactor(const IntersectionPoint& p);
    double calculateSpecularFactor(const IntersectionPoint& p);
    Vector calculateDifuseIntensity(const IntersectionPoint& p) override;
    Vector calculateSpecularIntensity(const IntersectionPoint& p) override;
    void changeCoordinateCamera(Camera *camera) override;
    void changeCoordinateWorld(Camera *camera) override;
};


#endif 
