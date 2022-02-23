
#include "Utils/Matrix.hpp"
#include "Utils/Scene.hpp"
#include "Utils/Utils.hpp"
#include "Utils/Object_.hpp"
#include "Utils/Cylinder.hpp"
#include "Utils/Cone.hpp"
#include "Utils/Sphere.hpp"
#include "Utils/Cube.hpp"
#include "Utils/Material.hpp"
#include "Utils/Light.hpp"
#include "Utils/AmbientLight.hpp"
#include "Utils/PontualLight.hpp"
#include "Utils/SpotLight.hpp"
#include "Utils/Cluster.h"
#include <GL/glut.h>
#include <time.h>
#include <chrono>
#include <cmath>
#include <map>

# define M_PI 3.14159265358979323846
float *test;
Camera *frontCam;
Camera *topCam;
Camera *leftDiagonalCam;
Camera *sideCam;
Camera* customCam;
int matrixSizeC = 600;
int matrixSizeR = 400;
Scene *scene;
Object_ *obj;
IntersectionPoint *point;
int mainMenu;
int subMenu;
int row;
int column;
vector<Light *> lights;
vector<Object_ *> invisibleObjects;

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(matrixSizeC, matrixSizeR, GL_RGB, GL_FLOAT, test);
    glutSwapBuffers();
    glutPostRedisplay();
    
}

Matrix rotateY(Matrix m, double degree) {
    degree = degree * M_PI / 180;
    m(0, 0) = cos(degree);
    m(2, 0) = sin(degree);
    m(0, 2) = -sin(degree);
    m(2, 2) = cos(degree);
    return m;
}

Matrix rotateX(Matrix m, double degree) {
    degree = degree * M_PI / 180;
    m(1, 1) = cos(degree);
    m(2, 1) = -sin(degree);
    m(1, 2) = sin(degree);
    m(2, 2) = cos(degree);
    return m;
}

Matrix rotateZ(Matrix m, double degree) {
    degree = degree * M_PI / 180;
    m(0, 0) = cos(degree);
    m(0, 1) = -sin(degree);
    m(1, 0) = sin(degree);
    m(1, 1) = cos(degree);
    return m;
}


void onMouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        point = scene->checkPoint(matrixSizeC - y, x);
    }

}


void onKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        glutDestroyWindow(0);
        exit(0);
    } else if (key == '+') {
        scene->updateCamera(1);
    } else if (key == '-') {
        scene->updateCamera(2);
    } else if (key == 't'){
        scene->changeCamera(topCam);
    }else if (key == 'f') {
        scene->changeCamera(frontCam);
    }else if (key == 'd') {
        scene->changeCamera(leftDiagonalCam);
    }else if (key == 's') {
        scene->changeCamera(sideCam);
    }else if (key == 'c') {
        scene->changeCamera(customCam);
    }
    scene->printFullScene();
}

Cluster* createNightstand(float zOffset, map<string,Material*> materials, Vector normal) {
    auto* nightStandBody = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["Bronze"]);
    vector<Matrix> nightStandTransf;
    Matrix nightStandScaling = Matrix(4, 4, 0);
    nightStandScaling(0, 0) = 1;
    nightStandScaling(1, 1) = 1.3;
    nightStandScaling(2, 2) = 1.5;
    Matrix nightStandTranslation = Matrix(4, 4, 0);
    nightStandTranslation(0, 3) = 4;
    nightStandTranslation(1, 3) = 0.5;
    nightStandTranslation(2, 3) = -4 + zOffset;
    nightStandTransf.push_back(nightStandScaling);
    nightStandTransf.push_back(nightStandTranslation);
    nightStandBody->applyTransformation(nightStandTransf);

    auto* drawer1 = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["DarkBrown"]);
    vector<Matrix> drawer1Transf;


    Matrix drawer1Scaling = Matrix(4, 4, 0);
    drawer1Scaling(0, 0) = 0.1;
    drawer1Scaling(1, 1) = 0.3;
    drawer1Scaling(2, 2) = 1.3;
    drawer1Transf.push_back(drawer1Scaling);

    Matrix drawer1Translation = Matrix(4, 4, 0);
    drawer1Translation(0, 3) = 3.5;
    drawer1Translation(1, 3) = 1.5;
    drawer1Translation(2, 3) = -4.1 + zOffset;
    drawer1Transf.push_back(drawer1Translation);


    drawer1->applyTransformation(drawer1Transf);


    auto* drawer1Puller = new Cube(1, Utils::createPoint(3.5, 1.5, -4.1), materials["Pearl"]);
    vector<Matrix> drawer1PullerTransf;

    Matrix drawer1PullerScaling = Matrix(4, 4, 0);
    drawer1PullerScaling(0, 0) = 0.1;
    drawer1PullerScaling(1, 1) = 0.1;
    drawer1PullerScaling(2, 2) = 0.6;
    drawer1PullerTransf.push_back(drawer1PullerScaling);

    Matrix drawer1PullerTranslation = Matrix(4, 4, 0);
    drawer1PullerTranslation(0, 3) = 3.11;
    drawer1PullerTranslation(1, 3) = 1.5;
    drawer1PullerTranslation(2, 3) = -2.3 + zOffset;
    drawer1PullerTransf.push_back(drawer1PullerTranslation);


    drawer1Puller->applyTransformation(drawer1PullerTransf);


    auto* drawer2 = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["DarkBrown"]);
    vector<Matrix> drawer2Transf;


    Matrix drawer2Scaling = Matrix(4, 4, 0);
    drawer2Scaling(0, 0) = 0.1;
    drawer2Scaling(1, 1) = 0.3;
    drawer2Scaling(2, 2) = 1.3;
    drawer2Transf.push_back(drawer2Scaling);

    Matrix drawer2Translation = Matrix(4, 4, 0);
    drawer2Translation(0, 3) = 3.5;
    drawer2Translation(1, 3) = 1.1;
    drawer2Translation(2, 3) = -4.1 + zOffset;
    drawer2Transf.push_back(drawer2Translation);


    drawer2->applyTransformation(drawer2Transf);


    auto* drawer2Puller = new Cube(1, Utils::createPoint(3.5, 1.5, -4.1), materials["Pearl"]);
    vector<Matrix> drawer2PullerTransf;

    Matrix drawer2PullerScaling = Matrix(4, 4, 0);
    drawer2PullerScaling(0, 0) = 0.1;
    drawer2PullerScaling(1, 1) = 0.1;
    drawer2PullerScaling(2, 2) = 0.6;
    drawer2PullerTransf.push_back(drawer2PullerScaling);

    Matrix drawer2PullerTranslation = Matrix(4, 4, 0);
    drawer2PullerTranslation(0, 3) = 3.11;
    drawer2PullerTranslation(1, 3) = 1.1;
    drawer2PullerTranslation(2, 3) = -2.3 + zOffset;
    drawer2PullerTransf.push_back(drawer2PullerTranslation);


    drawer2Puller->applyTransformation(drawer2PullerTransf);



    auto* drawer3 = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["DarkBrown"]);
    vector<Matrix> drawer3Transf;


    Matrix drawer3Scaling = Matrix(4, 4, 0);
    drawer3Scaling(0, 0) = 0.1;
    drawer3Scaling(1, 1) = 0.3;
    drawer3Scaling(2, 2) = 1.3;
    drawer3Transf.push_back(drawer3Scaling);

    Matrix drawer3Translation = Matrix(4, 4, 0);
    drawer3Translation(0, 3) = 3.5;
    drawer3Translation(1, 3) = 0.7;
    drawer3Translation(2, 3) = -4.1 + zOffset;
    drawer3Transf.push_back(drawer3Translation);


    drawer3->applyTransformation(drawer3Transf);


    auto* drawer3Puller = new Cube(1, Utils::createPoint(3.5, 1.5, -4.1), materials["Pearl"]);
    vector<Matrix> drawer3PullerTransf;

    Matrix drawer3PullerScaling = Matrix(4, 4, 0);
    drawer3PullerScaling(0, 0) = 0.1;
    drawer3PullerScaling(1, 1) = 0.1;
    drawer3PullerScaling(2, 2) = 0.6;
    drawer3PullerTransf.push_back(drawer3PullerScaling);

    Matrix drawer3PullerTranslation = Matrix(4, 4, 0);
    drawer3PullerTranslation(0, 3) = 3.11;
    drawer3PullerTranslation(1, 3) = 0.7;
    drawer3PullerTranslation(2, 3) = -2.3 + zOffset;
    drawer3PullerTransf.push_back(drawer3PullerTranslation);

    drawer3Puller->applyTransformation(drawer3PullerTransf);

    auto* mesaColisao = new Cylinder(3.1f, 27.7f, *Utils::createPoint(0, 1, 0),
        Vector(1, 0, 0), materials["Pearl"]);
    auto* nightStand = new Cluster(mesaColisao);


    nightStand->addObject(nightStandBody);
    nightStand->addObject(drawer1);
    nightStand->addObject(drawer1Puller);
    nightStand->addObject(drawer2);
    nightStand->addObject(drawer2Puller);
    nightStand->addObject(drawer3);
    nightStand->addObject(drawer3Puller);

    return nightStand;

}

Cluster* createAbajour(float zOffset, map<string,Material*> materials, Vector normal) {
    auto* abajourHead = new Cylinder(0.27f, 0.4f, *Utils::createPoint(4, 2.6, -4.8 + zOffset), normal,
       materials["LightBlack"]);
   auto* abajourBody = new Cylinder(1.2f, 0.1f, *Utils::createPoint(4, 1.7, -4.8 + zOffset), normal,
       materials["Gold"]);
   auto* abajourBase = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["Pearl"]);

   vector<Matrix> abajourBaseTransf;
   Matrix abajourBaseScaling = Matrix(4, 4, 0);
   abajourBaseScaling(0, 0) = 0.5;
   abajourBaseScaling(1, 1) = 0.1;
   abajourBaseScaling(2, 2) = 0.5;
   Matrix abajourBaseTranslation = Matrix(4, 4, 0);
   abajourBaseTranslation(0, 3) = 4;
   abajourBaseTranslation(1, 3) = 1.8;
   abajourBaseTranslation(2, 3) = -4.6 + zOffset;
   abajourBaseTransf.push_back(abajourBaseScaling);
   abajourBaseTransf.push_back(abajourBaseTranslation);
   abajourBase->applyTransformation(abajourBaseTransf);

   auto* abajourCollision = new Cylinder(10.57f, 13.0f, *Utils::createPoint(3.75, 0, -13),
       Vector(0, 1, 0), materials["Pearl"]);

   auto* abajour = new Cluster(abajourCollision);

   abajour->addObject(abajourHead);
   abajour->addObject(abajourBody);
   abajour->addObject(abajourBase);

   return abajour;
}



Material* createMaterial(int r, int g, int b, float m) {
    float rNorm = r / (float) 255.0;
    float gNorm = g / (float) 255.0;
    float bNorm =  b / (float) 255.0;

    float ka[3] = { rNorm, gNorm, bNorm };
    float kd[3] = { max(rNorm-0.1f, 0.0f) , max(gNorm-0.1f, 0.0f), max(bNorm-0.1f, 0.0f) };
    float ks[3] = { max(rNorm - 0.3f, 0.0f) , max(gNorm - 0.3f, 0.0f), max(bNorm - 0.3f, 0.0f) };
    return new Material(ka, kd, ks, m);
}



int main(int argc, char **argv) {
// Materials ---------------------------------------------------------------------------------------------------------

    map<string,Material*> materials;

    // Green
    materials["Green"] = createMaterial(46, 204, 113, 1.0);
    
    //Pearl
    materials["Pearl"] = createMaterial(247, 237, 236, 1.0);

    //Orange
    materials["Orange"] = createMaterial(255, 87, 51, 1.0);

    //test
    materials["SkyBlue"] = createMaterial(90, 199, 255, 1.0);

    // Light Black
    materials["LightBlack"] = createMaterial(33, 47, 61, 1.0);

    // Bronze
    materials["Bronze"] = createMaterial(205, 127, 50, 1.0);

    //Gold
    materials["Gold"] = createMaterial(255, 215, 0, 1.0);

    // Dark Brown
    materials["DarkBrown"] = createMaterial(101, 67, 33, 1.0);

    // Japanese Red
    materials["JapaneseRed"] = createMaterial(208, 53, 51, 1.0);

// Lights -----------------------------------------------------------------

    AmbientLight *ambientLight = new AmbientLight(0.3f, 0.3f, 0.3f);
 
    PontualLight *luzPontual = new PontualLight(0.7f, 0.7f, 0.7f, -3.75, 10, -5);
    luzPontual->state = true;

    Vector dir(0, 1, 0);

    auto *abajourLight = new SpotLight(0.84f, 0.67f, 0.12f, 4, 3.7, -4.9, dir, 9);
    abajourLight->state = true;
    auto* rAbajourLight = new SpotLight(0.84f, 0.67f, 0.12f, 4, 3.7, -4.9 -6.3, dir, 9);

    auto *mainLight = new SpotLight(0.84f, 0.67f, 0.12f, 0, 5.76, -8, dir, 10);

    lights.emplace_back(abajourLight);
    lights.emplace_back(rAbajourLight);
    lights.emplace_back(mainLight);
    lights.emplace_back(luzPontual);

//  Room Creation -------------------------------------------------------
    //vector<Matrix> bedroomTransf;
    auto *bedroomCollision = new Cylinder(7.0f, 17.3f, Point{ 0, 0, -9}, Vector{0, 1, 0}, materials["Green"]);
    auto *bedroom = new Cluster(bedroomCollision);

    //Matrix bedroomTranslation = Matrix(4, 4, 0);
    ////bedroomTranslation(1, 3) = 2;
    //bedroomTranslation(2, 3) = -10;
    ////bedroomTransf.push_back(zwallScaling);
    //bedroomTransf.push_back(bedroomTranslation);
    //bedroom->applyTransformation(bedroomTransf);

    Vector normal(0, 1, 0);
    vector<Object_ *> objects;

    auto *zWall = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["JapaneseRed"]);
    vector<Matrix> zWallTransf;
    Matrix zwallScaling = Matrix(4, 4, 0);
    zwallScaling(0, 0) = 1.0 / 2.0;
    zwallScaling(1, 1) = 7;
    zwallScaling(2, 2) = 12;

    Matrix zWallTranslation = Matrix(4, 4, 0);
    zWallTranslation(2, 3) = -2;
    zWallTranslation(0, 3) = 5;
    zWallTransf.push_back(zwallScaling);
    zWallTransf.push_back(zWallTranslation);
    zWall->applyTransformation(zWallTransf);

    auto *xWall = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["LightBlack"]);
    vector<Matrix> xWallTransf;
    Matrix xWallScaling = Matrix(4, 4, 0);
    xWallScaling(0, 0) = 10;
    xWallScaling(1, 1) = 7;
    xWallScaling(2, 2) = 1.0 / 2.0;
    Matrix xWallTranslation = Matrix(4, 4, 0);
    xWallTranslation(2, 3) = -14;
    xWallTransf.push_back(xWallScaling);
    xWallTransf.push_back(xWallTranslation);
    xWall->applyTransformation(xWallTransf);

    auto *floor = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["Pearl"]);
    vector<Matrix> floorTransf;
    Matrix floorScaling = Matrix(4, 4, 0);
    floorScaling(0, 0) = 10;
    floorScaling(1, 1) = 1.0 / 2.0;
    floorScaling(2, 2) = 12;
    Matrix floorTranslation = Matrix(4, 4, 0);
    floorTranslation(2, 3) = -2;
    floorTransf.push_back(floorScaling);
    floorTransf.push_back(floorTranslation);
    floor->applyTransformation(floorTransf);


    auto* ceiling = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["Pearl"]);
    vector<Matrix> ceilingTransf;
    Matrix ceilingScaling = Matrix(4, 4, 0);
    ceilingScaling(0, 0) = 11;
    ceilingScaling(1, 1) = 1.0 / 2.0;
    ceilingScaling(2, 2) = 12.5;
    Matrix ceilingTranslation = Matrix(4, 4, 0);
    ceilingTranslation(2, 3) = -2;
    ceilingTranslation(1, 3) = 7;
    ceilingTransf.push_back(ceilingScaling);
    ceilingTransf.push_back(ceilingTranslation);
    ceiling->applyTransformation(ceilingTransf);

// Bed ----------------------------------------------------------------------------------------------------------
 

    auto *mattress = new Cube(1, Utils::createPoint(-0.42, 0, -0.5), materials["Pearl"]);
    vector<Matrix> mattressTransf;
    Matrix mattressScaling = Matrix(4, 4, 0);
    mattressScaling(0, 0) = 4.5;
    mattressScaling(1, 1) = 1.5;
    mattressScaling(2, 2) = 4;
    mattressTransf.push_back(mattressScaling);

    Matrix mattressTranslation = Matrix(4, 4, 0);
    mattressTranslation(2, 3) = -6;
    mattressTranslation(0, 3) = 4;
    mattressTransf.push_back(mattressTranslation);


    mattress->applyTransformation(mattressTransf);


    auto *bedHead = new Cube(1, Utils::createPoint(0, 0, -0.5), materials["DarkBrown"]);
    vector<Matrix> bedHeadTransf;
    Matrix bedHeadScaling = Matrix(4, 4, 0);
    bedHeadScaling(0, 0) = 0.2;
    bedHeadScaling(1, 1) = 2;
    bedHeadScaling(2, 2) = 4;
    Matrix bedHeadTranslation = Matrix(4, 4, 0);
    bedHeadTranslation(2, 3) = -5.999;
    bedHeadTranslation(1, 3) = 0.5;
    bedHeadTranslation(0, 3) = 4.5;
    bedHeadTransf.push_back(bedHeadScaling);
    bedHeadTransf.push_back(bedHeadTranslation);
    bedHead->applyTransformation(bedHeadTransf);

    auto *bedHeadCollision = new Cylinder(3.0f, 0.1f, *Utils::createPoint(3.4, 1.8, -6),
                                    Vector(0, 0, -1), materials["Gold"]);

    auto *bedCollision = new Cylinder(4.0f, 18.2f, *Utils::createPoint(3.3, 0.75, -5.5),
                                      Vector(0, 0, -1), materials["Pearl"]);
    auto *bed = new Cluster(bedCollision);

    bed->addObject(mattress);
    bed->addObject(bedHead);
    bedroom->addObject(bed);


// -------------------------------------------- Left Nightstand -----------------------------------------------------------------
    Cluster* nightStandBody = createNightstand(0, materials, normal);
    Cluster* nightStandAbajour = createAbajour(0, materials, normal);

    vector<Matrix> transf;
    Matrix matrix = Matrix(4, 4, 0);
 
   //matrix = rotateY(matrix, 180);
   transf.push_back(matrix);


    bedroom->addObject(nightStandBody);
    bedroom->addObject(nightStandAbajour);

    Cluster* rNightstand = createNightstand(-6.3f, materials, normal);
    Cluster* rNightstandAbajour = createAbajour(-6.3f, materials, normal);
    bedroom->addObject(rNightstand);
    bedroom->addObject(rNightstandAbajour);


// Chandelier --------------------------------------------------------------------------------------------------------
    auto *cable = new Cylinder(1.0f, 0.03f, *Utils::createPoint(0, 6, -8),
            Vector(0, 1, 0), materials["Pearl"]);
    auto *cone = new Cone(0.5f, 1.5f, Utils::createPoint(0, 5.75, -8),
                          Vector(0, 1, 0), materials["Pearl"]);
    auto *lightBulb = new Sphere(0.1f,Utils::createPoint(0, 5.76, -8),materials["Pearl"]);

    auto *chandelierCollision = new Cylinder(1.3f, 5.35f, *Utils::createPoint(0, 5.66, -7),
                                      Vector(0, 1, 0), materials["Pearl"]);

    auto *chandelier = new Cluster(chandelierCollision);
    chandelier->addObject(cable);
    chandelier->addObject(cone);
    chandelier->addObject(lightBulb);

    bedroom->addObject(chandelier);


    // Closet

    auto* windowExt1 = new Cube(0.5, Utils::createPoint(0, 0, -0.5), materials["Pearl"]);
    vector<Matrix> windowExt1Transf;
    Matrix windowExt1Scalling = Matrix(4, 4, 0);
    windowExt1Scalling(0, 0) = 3.5;
    windowExt1Scalling(1, 1) = 11;
    windowExt1Scalling(2, 2) = 0.08;
    Matrix windowExt1Translation = Matrix(4, 4, 0);
    windowExt1Translation(0, 3) = 1;
    windowExt1Translation(1, 3) = 0.6;
    windowExt1Translation(2, 3) = -13.5;
    windowExt1Transf.push_back(windowExt1Scalling);
    windowExt1Transf.push_back(windowExt1Translation);
    windowExt1->applyTransformation(windowExt1Transf);
    bedroom->addObject(windowExt1);

    auto* windowInt1 = new Cube(0.5, Utils::createPoint(0, 0, -0.5), materials["DarkBrown"]);
    vector<Matrix> windowInt1Transf;
    Matrix windowInt1Scalling = Matrix(4, 4, 0);
    windowInt1Scalling(0, 0) = 2;
    windowInt1Scalling(1, 1) = 10;
    windowInt1Scalling(2, 2) = 0.1;
    Matrix windowInt1Translation = Matrix(4, 4, 0);
    windowInt1Translation(0, 3) = 1;
    windowInt1Translation(1, 3) = 0.8;
    windowInt1Translation(2, 3) = -13.41;
    windowInt1Transf.push_back(windowInt1Scalling);
    windowInt1Transf.push_back(windowInt1Translation);
    windowInt1->applyTransformation(windowInt1Transf);
    bedroom->addObject(windowInt1);

    auto* window1Puller = new Sphere(0.17f, Utils::createPoint(0.35, 3.7, -13.5), materials["Gold"]);
    bedroom->addObject(window1Puller);


    auto* windowExt2 = new Cube(0.5, Utils::createPoint(0, 0, -0.5), materials["Pearl"]);
    vector<Matrix> windowExt2Transf;
    Matrix windowExt2Scalling = Matrix(4, 4, 0);
    windowExt2Scalling(0, 0) = 3.5;
    windowExt2Scalling(1, 1) = 11;
    windowExt2Scalling(2, 2) = 0.08;
    Matrix windowExt2Translation = Matrix(4, 4, 0);
    windowExt2Translation(0, 3) = -0.775;
    windowExt2Translation(1, 3) = 0.6;
    windowExt2Translation(2, 3) = -13.5;
    windowExt2Transf.push_back(windowExt2Scalling);
    windowExt2Transf.push_back(windowExt2Translation);
    windowExt2->applyTransformation(windowExt2Transf);
    bedroom->addObject(windowExt2);

    auto* windowInt2 = new Cube(0.5, Utils::createPoint(0, 0, -0.5), materials["DarkBrown"]);
    vector<Matrix> windowInt2Transf;
    Matrix windowInt2Scalling = Matrix(4, 4, 0);
    windowInt2Scalling(0, 0) = 2;
    windowInt2Scalling(1, 1) = 10;
    windowInt2Scalling(2, 2) = 0.1;
    Matrix windowInt2Translation = Matrix(4, 4, 0);
    windowInt2Translation(0, 3) = -0.775;
    windowInt2Translation(1, 3) = 0.8;
    windowInt2Translation(2, 3) = -13.41;
    windowInt2Transf.push_back(windowInt2Scalling);
    windowInt2Transf.push_back(windowInt2Translation);
    windowInt2->applyTransformation(windowInt2Transf);
    bedroom->addObject(windowInt2);

    auto* window2Puller = new Sphere(0.17f, Utils::createPoint(-0.08, 3.7, -13.5), materials["Gold"]);
    bedroom->addObject(window2Puller);

    auto* ball = new Cube(0.3, Utils::createPoint(4.5, 0.5, -13.7), materials["Green"]);
    //bedroom->addObject(ball);

// Add walls ---------------------------------------------------------
    bedroom->addObject(zWall);
    bedroom->addObject(xWall);
    bedroom->addObject(floor);
    bedroom->addObject(ceiling);

    objects.push_back(bedroom);

// Grid indo --------------------------------------------------------------
    float gridSize = 4;
    float zGrid = -4;

// Camera Coordinates ----------------------------------------------------------
//Top -> y
    Point *pCoordTopCam = Utils::createPoint(0, 21, -11.3);
    Point *pTopCamLookAt = Utils::createPoint(0, 0, -11.3);
    Point *pTopCamViewUp = Utils::createPoint(0, 19, -12);
    
//Side -> z
    Point* pCoordSideCam = Utils::createPoint(0.4, 4, 5);
    Point* pSideCamLookAt = Utils::createPoint(0.4, 4.15, -6.5);
    Point* pSideCamViewUp = Utils::createPoint(0.4, 5, 5);
//Front -> x
    Point* pCoordFrontCam = Utils::createPoint(-18, 6, -8.3);
    Point* pFrontCamLookAt = Utils::createPoint(0,6,-8.3);
    Point* pFrontCamViewUp = Utils::createPoint(-20,7,-8.3);
//Diagonal -> x e z
    Point* pCoordDiagonalCam = Utils::createPoint(-9, 6, 7);
    Point* pDiagonalCamLookAt = Utils::createPoint(0,4.5,-6);
    Point* pDiagonalCamViewUp = Utils::createPoint(-9,7,7);

//// Custom Cam
  //Point* pCoordCustomCam = Utils::createPoint(0, 0, 12);
  //Point* pCustomCamLookAt = Utils::createPoint(0, 1, 0);
  //Point* pCustomCamViewUp = Utils::createPoint(0, 1, 12);

    //// Left Abajour Cam Front
    //Point* pCoordCustomCam = Utils::createPoint(0, 3, -5);
    //Point* pCustomCamLookAt = Utils::createPoint(1, 3, -5);
    //Point* pCustomCamViewUp = Utils::createPoint(0, 4, -5);


    //// Left Abajour Cam side
    //Point* pCoordCustomCam = Utils::createPoint(4, 3, -1);
    //Point* pCustomCamLookAt = Utils::createPoint(4, 3, -2);
    //Point* pCustomCamViewUp = Utils::createPoint(4, 4, -1);

    // Left Abajour Cam top
    //Point* pCoordCustomCam = Utils::createPoint(4, 6, -3);
    //Point* pCustomCamLookAt = Utils::createPoint(4, 2, -6);
    //Point* pCustomCamViewUp = Utils::createPoint(4, 3, -6);

    // bottom abajour Cam
    //Point* pCoordCustomCam = Utils::createPoint(0, 2, -5);
    //Point* pCustomCamLookAt = Utils::createPoint(1, 3.3, -5);
    //Point* pCustomCamViewUp = Utils::createPoint(0, 3, -5);

      // bottom chandelier Cam
 /*   Point* pCoordCustomCam = Utils::createPoint(0, 0, -9.8);
    Point* pCustomCamLookAt = Utils::createPoint(0, 6, -9.8);
    Point* pCustomCamViewUp = Utils::createPoint(0.5, 1.5, -10);*/

    // bed up cam
    Point* pCoordCustomCam = Utils::createPoint(2, 16, -8.3);
    Point* pCustomCamLookAt = Utils::createPoint(0, 0, -8.3);
    Point* pCustomCamViewUp = Utils::createPoint(3, 19, -12);


    frontCam = new Camera(pCoordFrontCam, pFrontCamLookAt, pFrontCamViewUp, gridSize, zGrid, matrixSizeC);
    topCam = new Camera(pCoordTopCam, pTopCamLookAt, pTopCamViewUp, gridSize, zGrid, matrixSizeC);
    leftDiagonalCam = new Camera(pCoordDiagonalCam, pDiagonalCamLookAt, pDiagonalCamViewUp, gridSize, zGrid, matrixSizeC);
    sideCam = new Camera(pCoordSideCam, pSideCamLookAt, pSideCamViewUp, gridSize, zGrid, matrixSizeC);
    customCam = new Camera(pCoordCustomCam, pCustomCamLookAt, pCustomCamViewUp, gridSize, zGrid, matrixSizeC);

    scene = new Scene(frontCam, objects, ambientLight, lights);

// ------------------------------------- Functions ---------------------------------------------------------------------
    scene->printFullScene();

// ------------------------------------- Window ----------------------------------------------------------------------
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(matrixSizeC, matrixSizeR);
    glutInitWindowPosition((1366 / 2) - matrixSizeC / 2, (768 / 2) - (matrixSizeR + 50) / 2);
    glutCreateWindow("Bedroom");

    test = scene->getSceneData();
    glutDisplayFunc(display);
    glutMouseFunc(onMouseButton);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();
    return 0;
}
