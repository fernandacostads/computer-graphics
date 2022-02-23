#include "Cube.hpp"
#include "Utils.hpp"
#include "Plane.hpp"
#include "Cluster.h"

Cube::Cube(double cEdge, Point* cCenter, Material* material): edge(cEdge), center(cCenter),
Object_("Cube", false, material){

    Point* p1 = Utils::createPoint(center->x - edge/2, center->y + edge, center->z + edge/2);
    Point* p2 = Utils::createPoint(center->x - edge/2, center->y + edge, center->z - edge/2);
    Point* p3 = Utils::createPoint(center->x + edge/2, center->y + edge, center->z - edge/2);
    Point* p4 = Utils::createPoint(center->x + edge/2, center->y + edge, center->z + edge/2);
    Point* p5 = Utils::createPoint(center->x - edge/2, center->y, center->z + edge/2);
    Point* p6 = Utils::createPoint(center->x - edge/2, center->y, center->z - edge/2);
    Point* p7 = Utils::createPoint(center->x + edge/2, center->y, center->z - edge/2);
    Point* p8 = Utils::createPoint(center->x + edge/2, center->y, center->z + edge/2);

    vertices.push_back(createVertex(p1, "V1"));
    vertices.push_back(createVertex(p2, "V2"));
    vertices.push_back(createVertex(p3, "V3"));
    vertices.push_back(createVertex(p4, "V4"));
    vertices.push_back(createVertex(p5, "V5"));
    vertices.push_back(createVertex(p6, "V6"));
    vertices.push_back(createVertex(p7, "V7"));
    vertices.push_back(createVertex(p8, "V8"));

    triangles.push_back(createTriangle(vertices[0], vertices[3], vertices[2], "F1"));
    triangles.push_back(createTriangle(vertices[2], vertices[1], vertices[0], "F2"));
    triangles.push_back(createTriangle(vertices[6], vertices[5], vertices[2], "F3"));
    triangles.push_back(createTriangle(vertices[5], vertices[1], vertices[2], "F4"));
    triangles.push_back(createTriangle(vertices[7], vertices[6], vertices[3], "F5"));
    triangles.push_back(createTriangle(vertices[6], vertices[2], vertices[3], "F6"));
    triangles.push_back(createTriangle(vertices[4], vertices[7], vertices[3], "F7"));
    triangles.push_back(createTriangle(vertices[3], vertices[0], vertices[4], "F8"));
    triangles.push_back(createTriangle(vertices[6], vertices[7], vertices[4], "F9"));
    triangles.push_back(createTriangle(vertices[4], vertices[5], vertices[6], "F10"));
    triangles.push_back(createTriangle(vertices[0], vertices[5], vertices[4], "F11"));
    triangles.push_back(createTriangle(vertices[5], vertices[0], vertices[1], "F12"));

}

Vector Cube::calculateNormal(Point* p){
    return normal;
}

tuple<Point*,Object_*> Cube::lineIntersection(Point *pP0, const Vector &pV0) {

    vector< pair<Point*, Triangle*> > intTriangle;
    for (unsigned int i = 0; i < triangles.size()-1; i +=2) {
        Point *p = triangles[i]->p->intersectionLinePlane(*pP0, pV0);

        if (p) {
            Vector p1p = Utils::pointSubtraction(*triangles[i]->p1->p, *p);
            Vector p2p = Utils::pointSubtraction(*triangles[i]->p2->p, *p);
            Vector p3p = Utils::pointSubtraction(*triangles[i]->p3->p, *p);

            if (triangles[i]->validatePointTriangle(p1p,p2p,p3p)) {
                intTriangle.emplace_back(make_pair(p, triangles[i]));
                normal = triangles[i]->p->normal;

            } else {
                p1p = Utils::pointSubtraction(*triangles[i + 1]->p1->p, *p);
                p2p = Utils::pointSubtraction(*triangles[i + 1]->p2->p, *p);
                p3p = Utils::pointSubtraction(*triangles[i + 1]->p3->p, *p);

                if (triangles[i+1]->validatePointTriangle(p1p,p2p,p3p)) {
                    intTriangle.emplace_back(make_pair(p, triangles[i + 1]));
                    normal = triangles[i + 1]->p->normal;
                } else {
                    delete p;
                }
            }
        }
        if(intTriangle.size() == 2){
            break;
        }
    }


    if(!intTriangle.empty()) {
        if (intTriangle.size() >= 2) {
            if (Utils::distanceBetweenPoints(pP0, intTriangle[0].first) <
                Utils::distanceBetweenPoints(pP0, intTriangle[1].first)) {
                normal = intTriangle[0].second->p->normal;
            }
            else {
                normal = intTriangle[1].second->p->normal;
            }
        }
        else {
            normal = intTriangle[0].second->p->normal;
        }
    }
    if(intTriangle.empty()) {
        return make_tuple(nullptr, this);
    }
    else if(intTriangle.size() == 1) {
        return make_tuple(intTriangle[0].first, this);
    }
    else {
        if(Utils::distanceBetweenPoints(intTriangle[0].first, pP0) < Utils::distanceBetweenPoints(intTriangle[1].first, pP0)) {
            return make_tuple(intTriangle[0].first, this);
        }
        else {
            return make_tuple(intTriangle[1].first, this);
        }
    }

}

Vertex* Cube::createVertex(Point* point, const string& identifier){
    auto v = new Vertex();
    v->p = point;
    v->id = identifier;
    return v;
}

Edge* Cube::createEdge(Vertex *pi, Vertex *pf, const string& id) {
    auto numberOfEdges = new Edge;
    numberOfEdges->id = id;
    numberOfEdges->finalVertex = pf;
    numberOfEdges->initialVertex = pi;
    return numberOfEdges;
}

Triangle* Cube::createTriangle(Vertex *v1, Vertex *v2, Vertex *v3, const string& id){
    Vector p1p2 = Utils::pointSubtraction(*v1->p, *v2->p);
    Vector p1p3 = Utils::pointSubtraction(*v1->p, *v3->p);
    return new Triangle(id, v1, v2, v3, new Plane(v1->p, Utils::findNormal(p1p2, p1p3)));
}

void Cube::changeCoordinateCamera(Camera *camera) {
    camera->changeWorldCamera(center);
    for (auto vertex: vertices) {
        camera->changeWorldCamera(vertex->p);
    }
    for (auto triangle: triangles) {
        triangle->changeCoordinateWorld(camera);
    }
}

void Cube::changeCoordinateWorld(Camera *camera) {
    camera->changeCameraWorld(center);
    for (auto vertex: vertices) {
        camera->changeCameraWorld(vertex->p);
    }
    for (auto triangle: triangles) {
        triangle->changeCoordinateCamera(camera);
    }

}

Point *Cube::firstIntersection(const Point &pP0, const Vector &pVector0) {
    return nullptr;
}



Point *Cube::getCenter() {
    return center;
}

void Cube::applyTransformation(vector<Matrix> &pTransfMatrixes) {
    for(auto triangle :triangles){
        triangle->applyTransformation(pTransfMatrixes);
    }
    Matrix aux = Matrix(4,1,0);
    for (auto vertex: vertices) {
        aux(0,0) = vertex->p->x;
        aux(1,0) = vertex->p->y;
        aux(2,0) = vertex->p->z;
        aux(3,0) = 1;
        for (auto matrix: pTransfMatrixes) {
            aux = matrix * aux;
        }
        vertex->p->x = aux(0,0);
        vertex->p->y = aux(1,0);
        vertex->p->z = aux(2,0);

    }
    aux(0,0) = normal.x;
    aux(1,0) = normal.y;
    aux(2,0) = normal.z;
    aux(3,0) = 0;
    for (auto matrix: pTransfMatrixes) {
        aux = matrix * aux;
    }
    normal.x = aux(0,0);
    normal.y = aux(1,0);
    normal.z = aux(2,0);
}

tuple<Point, Point> Cube::Limits()
{
    Point max;
    max.x = vertices[0]->p->x;
    max.y = vertices[0]->p->y;
    max.z = vertices[0]->p->z;
    Point min;
    min.x = vertices[0]->p->x;
    min.y = vertices[0]->p->y;
    min.z = vertices[0]->p->z;
    for(unsigned int i = 1; i < vertices.size(); i++) {
        if(vertices[i]->p->x > max.x){
            max.x = vertices[i]->p->x;
        }
        if(vertices[i]->p->y > max.y){
            max.y = vertices[i]->p->y;
        }
        if(vertices[i]->p->z > max.z){
            max.z = vertices[i]->p->z;
        }
        if(vertices[i]->p->x < min.x){
            min.x = vertices[i]->p->x;
        }
        if(vertices[i]->p->y < min.y){
            min.y = vertices[i]->p->y;
        }
        if(vertices[i]->p->z < min.z){
            min.z = vertices[i]->p->z;
        }
    }
    return make_tuple(max, min);
}
