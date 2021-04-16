# Rover Software [DEP]
This repository contains control & planning software for the RC prototype 
(i.e Space Prius)

DO NOT USE

## Terrain 
### Installation
We're moving from the toy implementation of Delaunay Triangulation to a blazing fast 2.5d triangulator called "fade2d." 

Python dependencies 
`cd terrain/visualizer && pip3 install -r requirements.txt`

CPP dependencies
 - libglfw3
 - libglfw3-dev
 - libglm-dev
 - libgmp
 - fade2d

#### To build fade2d
Navigate to the terrain directory, edit your distribution in the makefile and build the project. If on a unix compliant system make sure you have libgmp installed before you build.

Make sure that after you've compiled the fade2d library, move your respective binaries to the root terrain directory and build with the "compile" script (warning, on mac some changes to the compile script may be necessary, but I'm sure you can figure that out Justin :) )

### Usage
```
./compile && ./a.out && mv *.obj visualizer && mv *.xyz visualizer && cd visualizer && python3 viz.py

or 

./run 
```


## A* Implementation (DEPRECATED)
A simple graph search a* implementation that operates with given heuristics 
in the form of an std::unordered_map<int ID, int HEURISTIC>.

The test file can be run by compiling and running the main.cpp file.

` g++ main.cpp graph.cpp astar.cpp`

All the important class and struct definitions are outlined in graph.* files 
while the method implementation for A* is saved in astar.* files.

##  Delaunay Triangulation (DEPRECATED)
Toy implementation of delaunay triangulation of a mesh from PCD file. Make sure you have a glut distribution installed on your system.

Test file can be run by compiling and running the script compile script


``` 
$ chmod +x compile $ ./compile 
```

To run the script, pipe a PCD file to the compiled binary.

``` 
$ cat <PCD FILE>.pcd | ./a.out 
```

Once the 3D visualization shows up, you can navigate using standard control schemes. h, j, k, l keys to change camera angle and -+ to change zoom. These settings can be modified in the delaunay_triag.cpp file


## TODO
 - [x] implement a*
 - [x] implement delaunay triagulation
 - [x] Migrate to a faster & more reliable delaunay triangulation method
 - [x] Add decimation to delaunay triagulation mesh
 - [x] Make triangles into nodes on a graph
 - [x] algorithm for getting heuristics from decimated mesh
 - [x] Change a* to operate as a library
 - [x] algorithm to calculate penalties for certain triangles
 - [x] connect path from a* output
 - [x] interactive visualization layer i.e. point and click interaction for testing
 - [x] add floating point support for A* implementation
 - [ ] path smoothing
 - [ ] safety corridors
