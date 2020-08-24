// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 15 - Exercise 6, 7
/*
	6. Design and implement a bar graph class. Its basic data is a vector<double> 
	holding N values, and each value should represented by a "bar" that is a 
	rectangle where the height represents the value.
	7. Elaborate the bar graph class to allow labeling of the graph itself and its 
	individual bars. Allow the use of colour.
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

	Simple_window win{ Point{100,100}, xmax, ymax, "Exercise 6, 7" };

	// -----------------------------------------------------------------------------
	
	vector<double> heightValues{ 20, 100, 50, 450 };

	Graph_lib::BarChart bc(&win, heightValues);
	bc.setTitle("Heights Chart");
	bc.labelBars(true);
	bc.labelAxes("Heights", "cm");
	bc.fillBars(true);
	win.attach(bc);

	// -----------------------------------------------------------------------------

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
