#include <Fade_2D.h>
#include <stdio.h>
#include "someTools.h"

using namespace GEOM_FADE2D;




int ex8_triangulationExport_main()
{
	std::cout<<"* Example 8: Exporting a triangulation"<<std::endl;

	// * 1 *   Create some points
	std::vector<Point2> vPoints;
	generateCircle(6,25.0,25.0,10.0,10.0,vPoints);
	for(size_t i=0;i<vPoints.size();++i)
	{
		// Optional: Set an arbitrary custom index
		vPoints[i].setCustomIndex(int(i));
	}

	// * 2 *   Triangulate
	Fade_2D dt;
	dt.insert(vPoints);

	// * 3 *   Export (clears the Fade object)
	FadeExport fadeExport;
	bool bCustomIndices(true); // To retrieve custom indices also
	bool bClear(true); // Clear memory in $dt
	dt.exportTriangulation(fadeExport,bCustomIndices,bClear);

	//////////////////////////////////////////////////////
	// The Fade object has been cleared to avoid memory //
	// peaks. Now verify if we have received all data...//
	//////////////////////////////////////////////////////

	// * 4 *   Vertex output
	Visualizer2 visExp("example8_exported.ps");
	for(int vtxIdx=0;vtxIdx<fadeExport.numPoints;++vtxIdx)
	{
		double x,y;
		fadeExport.getCoordinates(vtxIdx,x,y);

		std::string s(" "+toString(vtxIdx));
		// Are there custom indices? Then add
		if(fadeExport.numCustomIndices==fadeExport.numPoints)
		{
			int customIdx(fadeExport.aCustomIndices[vtxIdx]);
			s.append("(customIdx="+toString(customIdx)+")");
		}
		std::cout<<"Vertex"<<s<<": "<<x<<" "<<y<<std::endl;
		Label label(Point2(x,y),s.c_str(),true,15);
		visExp.addObject(label,Color(CRED));
	}

	// * 5 *   Triangle output
	for(int triIdx=0;triIdx<fadeExport.numTriangles;++triIdx)
	{
		int vtxIdx0,vtxIdx1,vtxIdx2;
		fadeExport.getCornerIndices(triIdx,vtxIdx0,vtxIdx1,vtxIdx2);
		std::cout<<"Triangle "<<triIdx<<": "<<vtxIdx0<<" "<<vtxIdx1<<" "<<vtxIdx2<<std::endl;
		// Fetch also the coordinates and draw the edges
		double x0,y0;
		double x1,y1;
		double x2,y2;
		fadeExport.getCoordinates(vtxIdx0,x0,y0);
		fadeExport.getCoordinates(vtxIdx1,x1,y1);
		fadeExport.getCoordinates(vtxIdx2,x2,y2);
		Point2 p0(x0,y0);
		Point2 p1(x1,y1);
		Point2 p2(x2,y2);
		visExp.addObject(Segment2(p0,p1),Color(CBLACK));
		visExp.addObject(Segment2(p1,p2),Color(CBLACK));
		visExp.addObject(Segment2(p2,p0),Color(CBLACK));
		double midX((x0+x1+x2)/3.0);
		double midY((y0+y1+y2)/3.0);
		std::string text("T"+toString(triIdx));
		Label l(Point2(midX,midY),text.c_str(),true,15);
		visExp.addObject(l,Color(CBLUE));
	}

	// * 6 *   Neighbors output
	std::vector<std::pair<int,int> > vNeigs;
	fadeExport.extractTriangleNeighborships(vNeigs);
	for(size_t i=0;i<vNeigs.size();++i)
	{
		std::cout<<"Triangle "<<vNeigs[i].first<<" <-> Triangle "<<vNeigs[i].second<<std::endl;
	}
	visExp.writeFile(); // Write the postscript file

	// The above is for demonstration purposes, the easier way
	// to output FadeExport data is using its print() or writeObj()
	// function:
	//fadeExport.print();
	//fadeExport.writeObj("out.obj");

	return 0;
}



