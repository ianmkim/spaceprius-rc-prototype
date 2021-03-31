#include <Fade_2D.h>
#include <Visualizer3.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "someTools.h"
#include "render.h"
#include "mountain.h"

using namespace GEOM_FADE25D;

std::vector<Triangle2*>  triangles;

void renderScene(){
    int temporig, tempdest;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for(Triangle2* triangle : triangles){
        Point2 corner1 = *triangle->getCorner(0);
        Point2 corner2 = *triangle->getCorner(1);
        Point2 corner3 = *triangle->getCorner(2);
        
        glVertex3f(corner1.x(), corner1.z(), corner1.y());
        glVertex3f(corner2.x(), corner2.z(), corner2.y());

        glVertex3f(corner2.x(), corner2.z(), corner2.y());
        glVertex3f(corner3.x(), corner3.z(), corner3.y());

        glVertex3f(corner1.x(), corner1.z(), corner1.y());
        glVertex3f(corner3.x(), corner3.z(), corner3.y());
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

int random(int low, int high){
    return low + (std::rand() % (high - low + 1));
}

void decimate(std::vector<Point2> *points, float percentage){
    int amountToRemove = points->size() - int(percentage * points->size());
    if(amountToRemove < 0) return;
    for(int i = 0; i < amountToRemove; i++){
        points->erase(points->begin() + random(0, points->size()));
    }
}

int main(int argc, char** argv){
    std::vector<Point2> vInputPoints;
    //getInputPoints("", vInputPoints);
	getMountain(vInputPoints);

    std::cout << vInputPoints.size() << std::endl;
    decimate(&vInputPoints, 0.1);
    std::cout << vInputPoints.size() << std::endl;
    

    /*
    for(Point2 point : vInputPoints){
        std::cout <<  point << std::endl;
    }
    */

    Fade_2D dt;
    CloudPrepare cloudPrepare;
    cloudPrepare.add(vInputPoints);
    dt.insert(&cloudPrepare, true);
    dt.getTrianglePointers(triangles);
    
    /*
    for(Triangle2* triangle : triangles){
        std::cout << *triangle << std::endl;
    }
    */

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

    /*
    // write the mesh to .list and .obj
    write("mesh", dt);
    */
}

