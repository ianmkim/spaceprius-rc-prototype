#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include <set>
#include <queue>
#include "graph.h"

std::vector<Node> astarSearch(Graph *graph, std::unordered_map<int,float> heuristics, int start, int end);

bool addToOpen(std::vector<Node> open, Node neighbor);
#endif 
