#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <set>
#include "graph.h"
#include "astar.h"

/** util to visualize maps **/
void mapPrinter(std::unordered_map<int, int> myMap){
    std::cout << "{ ";
    for(auto elem : myMap)
       std::cout << "{" << elem.first << ": " << elem.second << "}, ";
    std::cout << "}" << std::endl;
}

/** util to vizualize vectors **/
void vectorPrinter(std::vector<Node> open){
    std::cout << "[";
    for(auto node :open){
        std::cout << node << ", ";
    } std::cout << "]" << std::endl;
}

/** util to vizualize vectors **/
void vectorPrinter(std::vector<int> open){
    std::cout << "[";
    for(auto node :open){
        std::cout << node << ", ";
    } std::cout << "]" << std::endl;
}


/** run the astar algorithm given heuristics, start, and end **/
std::vector<Node> astarSearch(Graph *graph, std::unordered_map<int, float> heuristics, int start, int end){
    std::unordered_map<int, Node> total_nodes;

    std::vector<Node> open;
    std::vector<int> closed;

    Node startNode(start);
    Node goalNode(end);

    open.push_back(start);
    std::make_heap(open.begin(), open.end());

    while(open.size() > 0){
        //std::cout << open.size() << std::endl;
        Node currentNode = open.front();
        total_nodes.insert({currentNode.id, currentNode});
        std::pop_heap(open.begin(), open.end());
        open.pop_back();
        closed.push_back(currentNode.id);

        if(currentNode == goalNode){
            std::vector<Node> path;
            while(currentNode.id != startNode.id){
                path.push_back(currentNode);
                currentNode = total_nodes.at(currentNode.parent);
            } path.push_back(startNode);
            return path;
        }

        auto neighbors = graph->get(currentNode.id);
        //mapPrinter(neighbors);
        //vectorPrinter(closed);

        for(auto kv : neighbors){
            Node neighbor(kv.first, currentNode.id);
            // err... lin space search no bueno
            if(std::find(closed.begin(), closed.end(), neighbor.id) != closed.end())
                continue;
            neighbor.g = currentNode.g + graph->get(currentNode.id, neighbor.id);
            neighbor.h = heuristics.at(neighbor.id);
            neighbor.f = neighbor.g + neighbor.h;
            
            /**
            std::cout << currentNode.g << std::endl;
            std::cout << graph->get(currentNode.id, neighbor.id) << std::endl;
            std::cout << heuristics.at(neighbor.id) << std::endl;
            std::cout << neighbor.h << std::endl;
            */

            if(addToOpen(open, neighbor)){
                open.push_back(neighbor);
                std::push_heap(open.begin(), open.end());
                //vectorPrinter(open);
            }
        }
    }
    std::vector<Node> empt_path;
    return empt_path;
}


/** check whether to add to open or not **/
bool addToOpen(std::vector<Node> open, Node neighbor){
    for(auto node : open)
        if(neighbor.id == node.id && neighbor.f > node.f) return false;
    return true;
}
