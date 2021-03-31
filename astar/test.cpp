#include "graph.h"
#include <queue>
#include <string>
#include <iostream>

int main(){
    DirectedGraph directedGraph;
    std::unordered_map<int, int> um;
    um.insert({2, 3});
    directedGraph.insert({1 , um});
    std::cout << directedGraph.at(1).at(2) << std::endl;
    /*
    std::priority_queue<Node> open;
    Node node1(1);
    node1.f = 10;
    Node node2(2);
    node2.f = 0;
    Node node3(3);
    node3.f = 20;


    open.push(node1);
    open.push(node2);
    open.push(node3);

    std::cout << open.top() << std::endl;
    open.pop();
    std::cout << open.top() << std::endl;
    open.pop();
    std::cout << open.top() << std::endl;
    open.pop();
    */
}
