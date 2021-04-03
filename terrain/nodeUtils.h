#ifndef NODEUTILS_H
#define NODEUTILS_H

#include <Fade_2D.h>
#include <vector>
#include <cmath>

using namespace GEOM_FADE25D;

/**
 * Q = ||X_j - X_i|| a B e ^(||X_j - X_i||/A_i + A_j)
 * X_i X_j are the geometric centers of cells j and i
 * A_i A_j are the areas of cells i and j
 * a b are penalty multipliers that take into account the slope
 */

float getArea(Triangle2* tri){
    return tri->getArea2D();
}

float length(float ve[]){
    return sqrt(ve[0]*ve[0] + ve[1]*ve[1] + ve[2]*ve[2]);
}

float dotProduct(float aVec[], float bVec[]){
    return aVec[0] * bVec[0] + aVec[1] * bVec[1] + aVec[2] * bVec[2];
}

float* crossProduct(float aVec[], float bVec[]){
    float* prod = new float[3];
    prod[0] = aVec[1] * bVec[2] - aVec[2] * bVec[1];
    prod[1] = aVec[2] * bVec[0] - aVec[0] * bVec[2];
    prod[2] = aVec[0] * bVec[1] - aVec[1] * bVec[0];
    return prod;
}

float getRelativeAngle(float norm1[], float norm2[]){
    return acos(dotProduct(norm1, norm2)/(length(norm1) * length(norm2)))* (180.0/3.141592653589793238463);
}

float* getNormalVec(Triangle2* tri){
    Point2 center = tri->getBarycenter();
    Point2 corner1 = *tri->getCorner(0);
    Point2 corner2 = *tri->getCorner(1);
    float vec1[3];
    vec1[0] = center.x() - corner1.x();
    vec1[1] = center.y() - corner1.y();
    vec1[2] = center.z() - corner1.z();

    float vec2[3];
    vec2[0] = center.x() - corner2.x();
    vec2[1] = center.y() - corner2.y();
    vec2[2] = center.z() - corner2.z();

    return crossProduct(vec1, vec2);
}

float getRelativeAngle(Triangle2* tri1, Triangle2* tri2){
    float *norm1 = getNormalVec(tri1);
    float *norm2 = getNormalVec(tri2);
    return getRelativeAngle(norm1, norm2);
}

float getAbsoluteAngle(Triangle2* tri){
    float *absoluteNorm = new float[3];
    absoluteNorm[0] = 0;
    absoluteNorm[1] = 1;
    absoluteNorm[2] = 0;

    float *triNorm = getNormalVec(tri);
    return getRelativeAngle(absoluteNorm, triNorm);
}

float getRegionalAngles(Triangle2* tri){
    float score = 0;
    for(int i = 0; i < 3; i++){
        Triangle2 *innerTri = tri->getOppositeTriangle(i);
        if(innerTri != NULL){
            // TODO swap out for something more sophisticated later
            score += getRelativeAngle(tri, innerTri);
        } else score += 45.0; // penalize corner nodes because we don't know what's on their edges (?)
    } return score;
}

float getRegionalDensity(Triangle2* tri){
    return 0.0;
}

#endif
