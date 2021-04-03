#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <set>
#include <math.h>

#include <Fade_2D.h>

#include "graph.h"
#include "astar.h"
#include "terrain.h"
#include "nodeUtils.h"

using namespace GEOM_FADE25D;

float distance(float x1, float y1, float z1,
        float x2, float y2, float z2) {
    float d = sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) +
                pow(z2 - z1, 2) * 1.0);
    return d;
}


std::unordered_map<int, Triangle2*> meshToIdMesh(std::vector<Triangle2*> triangles){
    std::unordered_map<int, Triangle2*> allTris;
    for(int i = 0; i < triangles.size(); i++){
        allTris.insert({i, triangles[i]});
    }
    return allTris;
}

int calculateHash(Triangle2* triangle){
    Point2 center = triangle->getBarycenter();
    int hash = int(triangle->getInteriorAngle2D(0)*100 + (center.x() * center.y() * center.z())*100 + triangle->getArea2D() * 10 + triangle->getMaxIndex());
    return hash;
}


std::unordered_map<double, int> getTriToId(std::unordered_map<int, Triangle2*> allTris){
    std::unordered_map<double, int> triToId;
    for(auto kv : allTris){
        int hash = calculateHash(kv.second);
        triToId.insert({hash, kv.first});
    } return  triToId;
}


std::unordered_map<int, float> heuristicsFromMesh(std::unordered_map<int, Triangle2*> triangles, int start){
    std::unordered_map<int, float> heuristics;
    Triangle2* thisTri = triangles.at(start);
    for(auto kv : triangles){
        Point2 thisCenter = thisTri->getBarycenter();
        Point2 center = kv.second->getBarycenter();
        int euDistance = distance(thisCenter.x(),thisCenter.y(),thisCenter.z(), center.x(), center.y(), center.z())*10;
        heuristics.insert({ kv.first, euDistance});
    } return heuristics;
}


Graph graphFromMesh(std::unordered_map<int, Triangle2*> allTris){
    Graph graph;
    std::unordered_map<double, int> triToId = getTriToId(allTris);
    
    for(auto kv : allTris){
        int id = kv.first;
        Triangle2 *thisTri = allTris.at(id);
        for(int i = 0; i < 3; i++){
            Triangle2 *innerTri = thisTri->getOppositeTriangle(i);
            if(innerTri != NULL){
                // get the centoids of both triangles
                Point2 thisCenter = thisTri->getBarycenter();
                Point2 center = innerTri->getBarycenter();

                // solve for the ID of the triangle using the hash value
                int otherTriId = triToId.at(calculateHash(innerTri));

                // calculate distance
                // TODO: add our own costs here
                float euDistance = distance(thisCenter.x(),thisCenter.y(),thisCenter.z(), center.x(), center.y(), center.z()) * 10;
                float cost = euDistance * exp(euDistance/(getArea(thisTri) + getArea(innerTri)));
                cost *= getRelativeAngle(thisTri, innerTri)+ 1;
                cost *= getAbsoluteAngle(innerTri)+ 1;
                cost *= getRegionalAngles(innerTri)+ 1;
                cost *= 1/(getArea(innerTri)*1000);
                
                // insert nodes & connect
                graph.connect(id, otherTriId, cost);
                graph.connect(otherTriId, id, cost);
            }
        }
    } return graph;
}

/*
Graph graphFromMesh(std::unordered_map<int, Triangle2*> allTris){
    Graph graph;

    std::set<int> visited;
    std::queue<int> toVisit;
    std::unordered_map<double, int> triToId = getTriToId(allTris);

    for(auto kv : allTris){
        toVisit.push(kv.first);
    }


    std::cout << allTris.size() << std::endl;
    int processedCount = 0;

    while(!toVisit.empty()){
        int id = toVisit.front();
        toVisit.pop();

        if(visited.find(id) == visited.end()){
            visited.insert(id);
            for(int i = 0; i < 3; i++){
                Triangle2 *thisTri = allTris.at(id);
                //std::cout << "this passed" << std::endl;
                Triangle2 *innerTri = thisTri->getOppositeTriangle(i);
                //std::cout << "POINTER: " << (innerTri == NULL) << std::endl;
                // i.e if the neighboring triangle exists
                if(innerTri != NULL){
                    // get the centoids of both triangles
                    Point2 thisCenter = thisTri->getBarycenter();
                    Point2 center = innerTri->getBarycenter();

                    // solve for the ID of the triangle using the hash value
                    int otherTriId = triToId.at(int(center.getMaxAbs() + center.x() + center.y()));

                    // calculate distance
                    // TODO: add our own costs here
                    float euDistance = distance(thisCenter.x(),thisCenter.y(),thisCenter.z(), center.x(), center.y(), center.z());

                    // insert nodes & connect
                    graph.connect(id, otherTriId, euDistance);
                    processedCount++;
                    // add triangle to visit
                    toVisit.push(otherTriId);
                }
            }
        }
    } 
    std::cout << "Number of triangles processed: " << processedCount << std::endl;
    return graph;
}
*/
