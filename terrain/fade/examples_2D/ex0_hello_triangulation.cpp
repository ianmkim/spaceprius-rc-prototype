#include <Fade_2D.h>
#include <stdio.h>

using namespace GEOM_FADE2D;

int ex0_hello_main()
{
	std::cout<<"* Example0:";
	std::cout<<"* Triangulate 4 points\n";
	std::cout<<"* Visualize the result\n\n";

	// Create a triangulation
	Fade_2D dt;

	// Create and insert 4 points
	Point2 p0(0.0,0.0);
	Point2 p1(0.0,1.0);
	Point2 p3(2,0.5);
	Point2 p2(0.5,0.5);
	dt.insert(p0);
	dt.insert(p1);
	dt.insert(p2);
	dt.insert(p3);

	// Draw
	dt.show("example0.ps");
	return 0;
}

