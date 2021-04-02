#ifndef TERRAIN_H
#define TERRAIN_H


#include <Fade_2D.h>
#include <vector> 
#include <unordered_map>
#include "graph.h"

using namespace GEOM_FADE25D;

int calculateHash(Triangle2* triangle);

std::unordered_map<int, Triangle2*> meshToIdMesh(std::vector<Triangle2*> triangles);

Graph graphFromMesh(std::unordered_map<int, Triangle2*> triangles);

std::unordered_map<int, int> heuristicsFromMesh(std::unordered_map<int, Triangle2*> triangles, int start);

std::unordered_map<double, int> getTriToId(std::unordered_map<int, Triangle2*> allTris);

#endif
