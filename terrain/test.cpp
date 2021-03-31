#include <Fade_2D.h>
#include <Visualizer3.h>
#include "someTools.h"

using namespace GEOM_FADE25D;

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
    std::vector<Point2> vInputPoints;
    getInputPoints("", vInputPoints);

    for(Point2 point : vInputPoints){
        std::cout <<  point << std::endl;
    }

    Fade_2D dt;
    CloudPrepare cloudPrepare;
    cloudPrepare.add(vInputPoints);
    dt.insert(&cloudPrepare, true);
    
    write("mesh", dt);
}

