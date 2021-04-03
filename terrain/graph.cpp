#include "graph.h"
#include <vector>
#include <unordered_map>

Graph::Graph() {
    this->directed = true;
    if(!this->directed)
        this->makeUndirected();
}

Graph::Graph(DirectedGraph directedGraph){
    this->directed = true;
    this->directedGraph = directedGraph;
    if(!directed)
        this->makeUndirected();
}

Graph::Graph(DirectedGraph directedGraph, bool directed){
    this->directed = directed;
    this->directedGraph = directedGraph;
    if(!directed)
        this->makeUndirected();
}

void Graph::makeUndirected(){
    for(auto kv : this->directedGraph){
        for(auto innerkv: kv.second){
            DirectedGraph::const_iterator got = this->directedGraph.find(innerkv.first);
            if(got == this->directedGraph.end()){
                // key not found
                std::unordered_map<int, float> new_om;
                new_om.insert({kv.first, innerkv.second});
                this->directedGraph.insert({innerkv.first, new_om});
            } else {
                this->directedGraph.at(innerkv.first).insert({kv.first, innerkv.second});
            }

        }
    }
}

void Graph::connect(int a, int b, float distance){
    DirectedGraph::const_iterator got = this->directedGraph.find(a);
    this->insertNode(a);
    this->insertNode(b);
    if(got == this->directedGraph.end()){
        // key not found
        std::unordered_map<int, float> new_om;
        new_om.insert({b, distance});
        this->directedGraph.insert({a, new_om});
    } else {
        // key found
        this->directedGraph.at(a).insert({b, distance});
    }
}

void Graph::connect(int a, int b){
    this->connect(a, b, 1);
}

std::unordered_map<int, float> Graph::get(int a){
    DirectedGraph::const_iterator got = this->directedGraph.find(a);
    if(got == this->directedGraph.end()){
        // key not found
        std::unordered_map<int,float> new_om;
        return new_om;
    } else {
        return this->directedGraph.at(a);
    }
}

float Graph::get(int a, int b){
    return this->directedGraph.at(a).at(b);
}

void Graph::insertNode(int a){
    std::unordered_map<int,bool>::const_iterator got = this->nodesUM.find(a);
    if(got == this->nodesUM.end()){
        // key is not found
        this->nodesUM.insert({a,a});
    }
}

std::vector<int> Graph::nodes(){
    std::vector<int> result;
    for(auto kv : this->nodesUM){
        result.push_back(kv.first);
    } return result;
}


