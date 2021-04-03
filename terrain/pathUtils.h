#ifndef PATHUTILS_H
#define PATHUTILS_H

#include <Fade_2D.h>
#include <vector>
#include <math.h>
#include "graph.h"

using namespace GEOM_FADE25D;

float* nodeToPoint(Node n, std::unordered_map<int,Triangle2*> *triangles){
    float *point = new float[3];
    Triangle2* tri = triangles->at(n.id);
    Point2 center = tri->getBarycenter();
    point[0] = center.x();
    point[1] = center.y();
    point[2] = center.z();
    return point;
}

float* normalize(float* a){
    float *newVec = new float[3];
    float length = sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]);
    newVec[0] = a[0]/length;
    newVec[1] = a[1]/length;
    newVec[2] = a[2]/length;
    return newVec;
}

float* scalarMultiply(float* vec, float dec){
    float *newVec = new float[3];
    newVec[0] = vec[0] * dec;
    newVec[1] = vec[1] * dec;
    newVec[2] = vec[2] * dec;
    return newVec;
}

float* addVec(float* a, float* b){
    float *newVec = new float[3];
    newVec[0] = a[0] + b[0];
    newVec[1] = a[1] + b[1];
    newVec[2] = a[2] + b[2];
    return newVec;
}

float* subtractVec(float* a, float* b){
    float *newVec = new float[3];
    newVec[0] = a[0] - b[0];
    newVec[1] = a[1] - b[1];
    newVec[2] = a[2] - b[2];
    return newVec;
}

float path_length(float ve[]){
    return sqrt(ve[0]*ve[0] + ve[1]*ve[1]);
}

float path_dotProduct(float aVec[], float bVec[]){
    return aVec[0] * bVec[0] + aVec[1] * bVec[1];
}

std::vector<float*> refinePath(std::vector<Node> path, std::unordered_map<int, Triangle2*> triangles){
    std::vector<float*> ret;
    ret.push_back(nodeToPoint(path[0], &triangles));
    float *home = nodeToPoint(path[path.size() -1], &triangles);

    float *pointQ = new float[3];
    float *pointR = new float[3];
    
    float *prevPoint = nodeToPoint(path.back(), &triangles); path.pop_back();
    while(path.size() > 1){
        float* curPoint = nodeToPoint(path.back(), &triangles); path.pop_back();
        float* nextPoint = nodeToPoint(path.back(), &triangles); path.pop_back();
        float* currentHeading = normalize(subtractVec(curPoint, prevPoint));
        float* nextHeading = normalize(subtractVec(nextPoint, curPoint));
        float angle = acos(path_dotProduct(currentHeading,nextHeading)/(path_length(currentHeading) * path_length(nextHeading)))* (180.0/3.141592653589793238463);

        if(angle >= 30){
            if(angle >= 90){
                path.pop_back();
                prevPoint = curPoint;
                continue;
            }
            pointQ = addVec(scalarMultiply(curPoint, 0.75), scalarMultiply(nextPoint, 0.25));
            pointR = addVec(scalarMultiply(curPoint, 0.25), scalarMultiply(nextPoint, 0.75));
            ret.push_back(pointQ);
            ret.push_back(pointR);
            prevPoint = pointR;
        }
    }

    if(std::find(ret.begin(), ret.end(), home) == ret.end()){
        ret.push_back(home);
    } return ret;
}

#endif 
