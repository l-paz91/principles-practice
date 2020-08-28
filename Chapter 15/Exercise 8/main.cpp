// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 15 - Exercise 8
/*
	Here is a collection of heights in centimetres together with the number of 
	people in a group of that height (rounded to the nearest 5cm): (170, 7), 
	(175,9), (180, 23), (185, 17), (190, 6), (195, 1). How would you graph that 
	data? If you can't think of anything better, do a bar graph. Remember to 
	provide axes and labels. Place the data in a file and read it from that file.
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

	Simple_window win{ Point{100,100}, xmax, ymax, "Exercise 8" };

	// -----------------------------------------------------------------------------
	
	//vector<CustomGraph::xyValues> values{
	//	CustomGraph::xyValues{175, 9},
	//	CustomGraph::xyValues{180, 23},
	//	CustomGraph::xyValues{56, 4},
	//	CustomGraph::xyValues{124, 14},
	//	CustomGraph::xyValues{144, 17}
	//};
	
	ScatterGraph sg{ &win, "heightData.txt" };
	sg.changeLabels("Height", "Age", Color::red, Color::red);
	sg.addChartTitle("Heights by Age");
	win.attach(sg);

	// -----------------------------------------------------------------------------

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
