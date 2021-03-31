#include "graph.h"
#include "astar.h"

int main(){
    Graph graph;
    graph.connect(1, 2, 111);
    graph.connect(1, 3, 85);
    graph.connect(2, 4, 104);
    graph.connect(2, 5, 140);
    graph.connect(2, 6, 183);
    graph.connect(3, 4, 230);
    graph.connect(3, 7, 67);
    graph.connect(7, 8, 191);
    graph.connect(7, 5, 64);
    graph.connect(4, 6, 171);
    graph.connect(4, 9, 170);
    graph.connect(4, 10, 220);
    graph.connect(5, 6, 107);
    graph.connect(8, 11, 91);
    graph.connect(8, 12, 85);
    graph.connect(11, 12, 120);
    graph.connect(12, 13, 184);
    graph.connect(13, 6, 55);
    graph.connect(13, 9, 115);
    graph.connect(9, 6, 123);
    graph.connect(9, 10, 189);
    graph.connect(9, 14, 59);
    graph.connect(14, 15, 81);
    graph.connect(10, 16, 102);
    graph.connect(15, 16, 126);

    graph.makeUndirected();

    std::unordered_map<int,int> heuristics;
    heuristics.insert({8,204});
    heuristics.insert({11, 247});
    heuristics.insert({1, 215});
    heuristics.insert({7, 137});
    heuristics.insert({16, 318});
    heuristics.insert({3, 164});
    heuristics.insert({9, 120});
    heuristics.insert({13, 47});
    heuristics.insert({4, 132});
    heuristics.insert({10, 257});
    heuristics.insert({14, 168});
    heuristics.insert({5, 75});
    heuristics.insert({15, 236});
    heuristics.insert({2, 153});
    heuristics.insert({12, 157});
    heuristics.insert({6, 0});

    std::cout << "{";
    for(auto kv : graph.directedGraph){
        std::cout << kv.first << ": {";
        for(auto kv1 : kv.second){
            std::cout << kv1.first << ": " << kv1.second << ", "; 
        }
        std::cout << "}, \n ";
    }
    std::cout << "}\n\n\n";

    auto path = astarSearch(&graph, heuristics, 1, 6);
    for(Node node : path){
        std::cout << node << std::endl;
    }
    return 0;
}
