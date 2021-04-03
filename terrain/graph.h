#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

class Node {
    public:
        int id;

        std::string label;
        int parent;

        float g;
        float h;
        float f;

        Node(int id, int parent){
            this->id = id;
            this->parent = parent;
            
            this->g = 0;
            this->h = 0;
            this->f = 0;
        }
        
        Node(int id){
            this->id = id;
  
            this->g = 0;
            this->h = 0;
            this->f = 0;
        }
};

typedef std::unordered_map<int, std::unordered_map<int,float>> DirectedGraph;

class Graph{
    public:
        DirectedGraph directedGraph;
        std::unordered_map<int, bool> nodesUM;
        bool directed;

        Graph();

        Graph(DirectedGraph directedGraph);

        Graph(DirectedGraph directedGraph, bool directed);

        Graph(bool directed);

        void makeUndirected();

        void connect(int a, int b );

        void connect(int a, int b, float distance);
    
        void insertNode(int a);

        std::unordered_map<int,float> get(int a);

        float get(int a, int b);

        std::vector<int> nodes();
};

inline bool operator==(const Node& lhs, const Node& rhs) {
    return lhs.id == rhs.id;
}

inline bool operator!=(const Node& lhs, const Node& rhs){
    return lhs.id == rhs.id;
}

inline bool operator<(const Node& lhs, const Node& rhs){
    return lhs.f > rhs.f;
}

inline bool operator<=(const Node& lhs, const Node& rhs){
    return lhs.f >= rhs.f;
}

inline std::ostream& operator<<(std::ostream& os, const Node& node){
    os << "(" << node.id << ", " << node.f <<")";
    return os;
}

#endif
