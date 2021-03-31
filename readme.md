# Rover Software
This repository contains control & planning software for the RC prototype 
(i.e Space Prius)

## A* Implementation
A simple graph search a* implementation that operates with given heuristics 
in the form of an std::unordered_map<int ID, int HEURISTIC>.

The test file can be run by compiling and running the main.cpp file.

` g++ main.cpp graph.cpp astar.cpp`

All the important class and struct definitions are outlined in graph.* files 
while the method implementation for A* is saved in astar.* files.

##  DelaunayTriangulation
Toy implementation of delaunay triangulation of a mesh from PCD file. Make sure you have a glut distribution installed on your system.

Test file can be run by compiling and running the script compile script


``` $ chmod +x compile $ ./compile ```

To run the script, pipe a PCD file to the compiled binary. ``` $ cat <PCD 
FILE>.pcd | ./a.out ```

Once the 3D visualization shows up, you can navigate using standard control schemes. h, j, k, l keys to change camera angle and -+ to change zoom. These settings can be modified in the delaunay_triag.cpp file
