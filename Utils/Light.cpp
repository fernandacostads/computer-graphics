#include "Light.hpp"


Light::Light(float r, float g, float b) {
    RGBIntensity = Vector(r, g, b);
    state = true;
}