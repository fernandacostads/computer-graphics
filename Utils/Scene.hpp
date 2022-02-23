#ifndef COMPUTACAOGRAFICA_SCENE_HPP
#define COMPUTACAOGRAFICA_SCENE_HPP
#include "Utils.hpp"
#include "Object_.hpp"
#include <vector>
#include "Camera.hpp"
#include "IntersectionPoint.hpp"
#include "../Bitmap/Bitmap.hpp"
#include "IntersectionPoint.hpp"
#include "Light.hpp"
#include "AmbientLight.hpp"
#include "Matrix.hpp"


class Scene {
public:
    Camera* camera;
    vector<Object_*> objects;
    Bitmap image;
    AmbientLight* ambientLight;
    vector<Light*> lights;

    Scene(Camera* pCamera, vector<Object_*> objects, AmbientLight* pAmbLight, vector<Light*> pLights);

    bool rayCasting(Point* pCoordObs, Point* pointGrid, IntersectionPoint &intersections);
    void paintObject(Point*** pGrid);
    void addObject(Object_* object);
    void printFullScene();
    IntersectionPoint* checkPoint(int row, int column);
    void visibleObjects();
    void changeCamera(Camera *pCamera);

    void updateCamera(int direction);
    float* getSceneData();
private:
    void startPainting();
    void startScene();

};


#endif
