# Rover Software
This repository contains control & planning software for the RC prototype 
(i.e Space Prius)

## Terrain 
We're moving from the toy implementation of Delaunay Triangulation to a fast as shit 2.5d triangulator called "fade2d." Navigate to the terrain directory, edit your distribution in the makefile and build the project. If on a unix compliant system make sure you have libgmp installed before you build.

Make sure that after you've compiled the fade2d library, move your respective binaries to the root terrain directory and build with the "compile" script (warning, on mac some changes to the compile script may be necessary, but I'm sure you can figure that out Justin :) )

make sure you have libglfw3 and libglfw3-dev installed (if you're on ubuntu that is)

Also make sure that you have libglm-dev installed

All the implementation is finished, to run the a* demo paste the following into the terminal. (Make sure that you have installed the python dependencies by running `pip3 install -r requirements.txt` in the ./terrain/visualizer directory)
```
./compile && a.out && mv *.obj visualizer && mv *.xyz visualizer && cd visualizer && python3 vis.py
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
 - [ ] Make triangles into nodes on a graph
 - [ ] algorithm for getting heuristics from decimated mesh
 - [x] Change a* to operate as a library
 - [ ] algorithm to calculate penalties for certain triangles
 - [ ] connect path from a* output
 - [ ] interactive visualization layer i.e. point and click interaction for testing
 - [ ] path smoothing
 - [ ] safety corridors
