#include <iostream>
#include <fstream>

#include <Fade_2D.h>
#include <Visualizer3.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <GLFW/glfw3.h>

#include "someTools.h"
#include "render.h"
#include "mountain.h"
#include "decimation.h"
#include "astar.h"
#include "terrain.h"
#include "pathUtils.h"

#define START 0
#define END 900

using namespace GEOM_FADE25D;

std::unordered_map<int, Triangle2*> triangles;
std::vector<Node> path;

void renderScene(){
    int temporig, tempdest;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for(auto kv : triangles){
        int id = kv.first;
        Triangle2 *triangle  = kv.second;
        if(id == START) glColor3f(0.0, 0.0, 1.0);
        if(id == END) glColor3f(0.0,0.0,1.0);

        Point2 corner1 = *triangle->getCorner(0);
        Point2 corner2 = *triangle->getCorner(1);
        Point2 corner3 = *triangle->getCorner(2);

        glVertex3f(corner1.x(), corner1.z(), corner1.y());
        glVertex3f(corner2.x(), corner2.z(), corner2.y());

        glVertex3f(corner2.x(), corner2.z(), corner2.y());
        glVertex3f(corner3.x(), corner3.z(), corner3.y());

        glVertex3f(corner1.x(), corner1.z(), corner1.y());
        glVertex3f(corner3.x(), corner3.z(), corner3.y());
        if(id == START || id == END) glColor3f(1.0, 1.0, 1.0);
    }
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);
    for(auto kv : triangles){
        int id = kv.first;
        Triangle2 *triangle  = kv.second;
        Point2 center = triangle->getBarycenter();
        glVertex3f(center.x(), center.z(), center.y());
    }
    glEnd();

    glColor3f(1.0, 0, 0);
    glBegin(GL_LINES);
    for(int i = 1; i < path.size(); i++){
        Point2 prevTri = triangles.at(path[i-1].id)->getBarycenter();
        Point2 nextTri = triangles.at(path[i].id)->getBarycenter();
        glVertex3f(prevTri.x(), prevTri.z(), prevTri.y());
        glVertex3f(nextTri.x(), nextTri.z(), nextTri.y());
    }
    glEnd();
    glutSwapBuffers();
}

void getInputPoints(const std::string& filename,
					std::vector<Point2>& vPointsOut){
	if(!filename.empty())
	{
		// Read terrain points from an ASCII file
		readXYZ(filename.c_str(),vPointsOut);
	}
	else
	{
		// No file given, create a random surface for the demo
		generateRandomSurfacePoints(
			100, // numPointsX
			100, // numPointsY
			200, // numCenters (waviness)
			0,0,0,100,100,50, // Bounds xmin,ymin,zmin,xmax,ymax,zmax
			vPointsOut, // Output vector
			1  // Seed (0 is random, >0 is static)
			);
	}
	std::cout<<"Original number of points: "<<vPointsOut.size()<<std::endl;
}

void write(const std::string& name, const Fade_2D& dt){
    dt.showGeomview((name + ".list").c_str());
    std::cout << gRed("Writing " + name + ".obj") << std::endl;
    dt.writeObj((name + ".obj").c_str());
}

int main(int argc, char** argv){
    // get input point clouds
    std::vector<Point2> vInputPoints;
	getMountain(vInputPoints);

    // decimate the point cloud based on random sampling
    std::cout << "Predecimation points size: " << vInputPoints.size() << std::endl;
    decimate(&vInputPoints, 0.1);
    std::cout << "Decimated points size: " << vInputPoints.size() << std::endl;

    // perform delaunay triangulation
    Fade_2D dt;
    CloudPrepare cloudPrepare;
    cloudPrepare.add(vInputPoints);
    dt.insert(&cloudPrepare, true);
    std::vector<Triangle2*> vecTriangles;
    dt.getTrianglePointers(vecTriangles);
    
    // assign a unique int id to each triangle in the mesh
    triangles = meshToIdMesh(vecTriangles);
    // calculate heuristics for A*
    auto heuristics = heuristicsFromMesh(triangles, START);
    // create a graph from the labeled mesh
    Graph graph = graphFromMesh(triangles);

    // perform A* shortest path search based on heuristics
    path = astarSearch(&graph, heuristics, START, END);
    // print path
    std::cout << "path length: " << path.size() << std::endl;
    std::cout << "PATH: ";
    for(Node n : path){
        std::cout << n << std::endl;
    }

    // write the mesh to disk
    write("mesh", dt);
    // write the centers of each triangles to disk alongside ID
    std::ofstream centerfile("centers.xyz");
    if(centerfile.is_open()){
        for(auto kv : triangles){
            int id = kv.first;
            Point2 center = kv.second->getBarycenter();
            centerfile << id << " " << center.x() << " " << center.y() << " " << center.z() << std::endl;
        }
    } else std::cout << "Unable to open centers file" << std::endl;
    
    // write the path file to disk
    std::ofstream pathfile("path.xyz");
    if(pathfile.is_open()){
        for(Node n : path){
            Triangle2 * tri = triangles.at(n.id);
            Point2 center = tri->getBarycenter();
            pathfile << center.x() << " " << center.y() << " " << center.z() << std::endl;
        } 
    } else std::cout << "Unable to open paths file" << std::endl;
    
    // write the refined path file to disk
    std::vector<float*> refinedPath = refinePath(path, triangles);
    std::ofstream refinedfile("refined.xyz");
    if(refinedfile.is_open()){
        for(float* n : refinedPath){
            refinedfile << n[0] << " " << n[1] << " " << n[2] << std::endl;
        }
    } else std::cout << "Unable to open paths file" << std::endl;

    // CODE FOR GLUT VISUALIZATION
    // only use for quick and dirty tasks, there's a better visualizer in python
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("");
    init();
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(inputKey);
    glutReshapeFunc(changeSize);
    glutMainLoop();
}

