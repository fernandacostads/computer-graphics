#include <utility>
#include <algorithm>
#include <cmath>
#include "Scene.hpp"
#include "Plane.hpp"
#include "Cluster.h"

Scene::Scene(Camera *pCamera, vector<Object_*> pObjects, AmbientLight* pAmbLight, vector<Light*> pLights) : camera(pCamera),
image(camera->numberOfHoles, camera->numberOfHoles), objects(pObjects), ambientLight(pAmbLight), lights(pLights) {
    startPainting();
    startScene();
}

void Scene::startScene(){
    for (auto object : objects) {
        object->changeCoordinateCamera(camera);
    }
    for (auto light : lights) {
        light->changeCoordinateCamera(camera);
    }
}

void Scene::addObject(Object_ *object) {
    objects.emplace_back(object);
}

void Scene::startPainting(){
    for (int i = 0; i < camera->numberOfHoles; ++i) {
        for (int j = 0; j < camera->numberOfHoles ; ++j) {
            image.setPixel(i,j,0.3f,0.7f,0.9f);
        }
    }
}

/// Função para comparar qual dos pontos de interseçao foi o primeiro.
/// \param i
/// \param j
/// \return
bool comparacaoDistancia(IntersectionPoint* i,IntersectionPoint* j){
    return (i->originDist < j->originDist);
}

IntersectionPoint interceptaObjeto(Object_* Object, Point *posObs, const Vector& lineObGrid){

    Point* pInt = nullptr;
    Object_* pObject = nullptr;

    tie(pInt, pObject) = Object->lineIntersection(posObs, lineObGrid);

    return IntersectionPoint(pInt, pObject, pInt ? Utils::distanceBetweenPoints(posObs, pInt) : 0);
}

void Scene::paintObject(Point*** pGrid){
    IntersectionPoint aux;
    bool auxDefined = false;
    Vector holeIntensity;
    for (int i = 0; i < camera->numberOfHoles; ++i) {
        for (int j = 0; j < camera->numberOfHoles; ++j) {
            Vector lineObGrid = Utils::pointSubtraction(*camera->observer, *pGrid[i][j]);
            for (auto &pObject : objects) {
                if (!pObject->visibility) {
                    IntersectionPoint pint = interceptaObjeto(pObject, camera->observer, lineObGrid);
                    if(pint.p && (!auxDefined || pint.originDist < aux.originDist)){
                        aux.originDist = pint.originDist;
                        aux.p = pint.p;
                        aux.object = pint.object;
                        auxDefined = true;
                    }
                }

            }
            if (auxDefined) {
                holeIntensity = ambientLight->calculateAmbientIntensity(aux);
                for (auto &l : lights) {
                    if(l->state) {
                        holeIntensity += l->calculateDifuseIntensity(aux);
                        holeIntensity += l->calculateSpecularIntensity(aux);
                    }
                }

                image.setPixel(j,i,(float)holeIntensity.x,(float)holeIntensity.y,
                                (float)holeIntensity.z);
            }
            else{
                image.setPixel(j,i,0.3f,0.7f,0.9f);
            }
            auxDefined = false;
        }
    }
}

float* Scene::getSceneData(){
    return image.getPixels();
}

void Scene::printFullScene() {
    IntersectionPoint intersections;
    paintObject(camera->cameraGrid);
}

IntersectionPoint* Scene::checkPoint(int row, int column) {
    auto *intersections = new IntersectionPoint();
    cout << "----------------------------------------------------------------------" << "\n";
    cout << "Center (" << row << ", "<< column <<"): " << camera->cameraGrid[row][column]->x << ", "
    << camera->cameraGrid[row][column]->y<< ", "<< camera->cameraGrid[row][column]->z << "\n";

    if(rayCasting(camera->observer, camera->cameraGrid[row][column], *intersections)){
        cout << "Object found: " << intersections->object->name << " - Point Intercepted: " << intersections->p->x
        << ", " <<intersections->p->y<< ", "<< intersections->p->z<< "\n";
        cout << "----------------------------------------------------------------------" << "\n";
        return intersections;
    }
    return nullptr;
}

void Scene::visibleObjects() {
    cout << "Visible objects: " << "\n";
    for(auto object : objects){
        if(object->visibility){
            cout << object->name << "\n";
        }
    }
    cout << endl;
}

void Scene::changeCamera(Camera *pCamera) {

    for(auto &object : objects){
        object->changeCoordinateWorld(camera);
        object->changeCoordinateCamera(pCamera);
    }
    for(auto &light : lights){
        light->changeCoordinateWorld(camera);
        light->changeCoordinateCamera(pCamera);
    }
    camera = pCamera;
}


void Scene::updateCamera(int direction) {
    Camera auxCam = *camera;
    if(direction == 1){
        camera->moveForwads();
        for (auto object : objects) {
            object->changeCoordinateWorld(&auxCam);
            object->changeCoordinateCamera(camera);
        }

        for (auto light : lights) {
            light->changeCoordinateWorld(&auxCam);
            light->changeCoordinateCamera(camera);
        }

    }
    else if(direction == 2){
        camera->moveBackwards();
        for (auto object : objects) {
            object->changeCoordinateWorld(&auxCam);
            object->changeCoordinateCamera(camera);
        }

        for (auto light : lights) {
            light->changeCoordinateWorld(&auxCam);
            light->changeCoordinateCamera(camera);
        }

    }

    printFullScene();
}

bool Scene::rayCasting(Point *pCoordObs, Point *pointGrid, IntersectionPoint &intersections) {
    Vector vectorObGrid = Utils::pointSubtraction(*pCoordObs, *pointGrid);

    Point* pInt = nullptr;
    Object_* pObject = nullptr;

    bool hit = false;

    for (auto &object : objects) {
        if(!object->visibility) {
            tie(pInt, pObject) = object->lineIntersection(pCoordObs, vectorObGrid);
            if (pInt) {
                if(!hit) {
                    intersections = IntersectionPoint(pInt, pObject,
                        Utils::distanceBetweenPoints(pCoordObs, pInt));
                    hit = true;
                } else {
                    auto dist = Utils::distanceBetweenPoints(pCoordObs, pInt);
                    if(dist < intersections.originDist){
                        intersections = IntersectionPoint(pInt, pObject, dist);
                    }
                }
            }
        }
    }
    return hit;
}

