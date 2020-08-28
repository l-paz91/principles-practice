// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 15 - Exercise 11
/*
	Find the average maximum temperatures for each month of the year for two or 
	more locations (e.g., Cambridge, England, and Cambridge, Massachusetts; there 
	are lots of towns called "Cambridge") and graph them together. As ever, be 
	careful with axes, labels, use of color, etc.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	const int xmax = 800;
	const int ymax = 600;

	Simple_window win{ Point{100,100}, xmax, ymax, "Exercise 11" };

	// -----------------------------------------------------------------------------
	
	vector<CustomGraph::xyValues> ohioT{
		CustomGraph::xyValues{1, 1},
		CustomGraph::xyValues{2, 4},
		CustomGraph::xyValues{3, 10},
		CustomGraph::xyValues{4, 17},
		CustomGraph::xyValues{5, 23},
		CustomGraph::xyValues{6, 27},
		CustomGraph::xyValues{7, 29},
		CustomGraph::xyValues{8, 28},
		CustomGraph::xyValues{9, 25},
		CustomGraph::xyValues{10, 18},
		CustomGraph::xyValues{11, 11},
		CustomGraph::xyValues{12, 5}
	};

	vector<CustomGraph::xyValues> londonT{
	CustomGraph::xyValues{1, 9},
	CustomGraph::xyValues{2, 9},
	CustomGraph::xyValues{3, 12},
	CustomGraph::xyValues{4, 15},
	CustomGraph::xyValues{5, 18},
	CustomGraph::xyValues{6, 21},
	CustomGraph::xyValues{7, 23},
	CustomGraph::xyValues{8, 23},
	CustomGraph::xyValues{9, 20},
	CustomGraph::xyValues{10, 16},
	CustomGraph::xyValues{11, 12},
	CustomGraph::xyValues{12, 9}
	};
	
	ScatterGraph sg{ &win, ohioT };
	sg.changeLabels("Month", "Temperature c", Color::red, Color::red);
	sg.addChartTitle("Yearly Temperature Highs in London UK vs London Ohio");
	sg.addDataSet(londonT, "London Temps", Color::blue);
	win.attach(sg);

	// -----------------------------------------------------------------------------

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
