
#include <stdio.h>
#include <iostream>
#include <Fade_2D.h>

using namespace std;


// Functions defined in other *.cpp files (declaration avoids additional header files)
int terrain_main();
int breaklines_main();
int segmentChecker_main();
int cutAndFill_main();
int removeBorderTriangles_main();
int meshImprovement_main();

void info()
{
	cout<<"\n\n\n\tWelcome to the Fade 25D examples"<<endl;
	cout<<"\t-------------------------------"<<endl<<endl;
	cout<<"\ta...Terrain Triangulation, Point Cloud Simplification, Data Export"<<endl;
	cout<<"\tb...Mesh Improvement - Smoothing, Valley/Ridge, Border Trimming"<<endl;
	cout<<"\tc...Breaklines, Cookie Cutter, ISO Contours, Height Queries"<<endl;
	cout<<"\td...Segment Checker"<<endl;
	cout<<"\te...Cut & Fill"<<endl;
}

int main()
{
	GEOM_FADE25D::Fade_2D dt;
	dt.printLicense();

	// Choose an example
	while(true)
	{
		info();
		char choice(0);
		cout << "\n\n\tChoose an example [a-e],q: ";
		cin>>choice;
		cout<<"\n\n\n"<<endl<<endl;
		switch(choice)
		{
			case 'a': terrain_main();break;
			case 'b': meshImprovement_main();break;
			case 'c': breaklines_main();break;
			case 'd': segmentChecker_main();break;
			case 'e': cutAndFill_main();break;
			case 'q':
			default:
				return 0;
		}
	}
}



