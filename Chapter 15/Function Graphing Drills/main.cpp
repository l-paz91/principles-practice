// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 15 - Drill 1, 2, 3, 4, 5
/*
	1. Make an empty 600-by-600 Window labeled "Function Graphs".

	2. Note that you'll need to make a project with the properties specified in the
	"installation of FLTK" note from the course website.

	3. You'll need to move Graph.cpp and Window.cpp into your project.

	4. Add an x axis and a y axis each of length 400, labeled "1 == 20 pixels" and 
	with a notch ever 20 pixels. The axes should cross at (300,300).

	5. Make both axes red.
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
	int xmax = 600;
	int ymax = 600;
	int axisLength = 400;
	int notches = 400 / 20;
	int yorigin = ymax / 2;
	int xorigin = xmax / 2;
	Point center(300, 300);

	Simple_window win{ Point{100,100}, xmax, ymax, "Function Graphs" };
	
	Axis xaxis(Axis::x, Point(100, yorigin), axisLength, notches, "x 1== 20 pixels");
	xaxis.set_color(Color::red);
	win.attach(xaxis);
	Axis yaxis(Axis::y, Point(xorigin, axisLength + 100), axisLength, notches, "y 1 == 20 pixels");
	yaxis.set_color(Color::red);
	win.attach(yaxis);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
