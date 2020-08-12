// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 15 - Drill 2
/*
	1. Graph the function  double one(double x) {return 1;} in the range [-10,11] 
	with (0,0) at (300,300) using 400 points and no scaling (in the window).
	2. Change it to use x scale 20 and y scale 20.
	3. From now on use that range, scale, etc. for all graphs.
	4. Add double slope(double x) {return x/2;} to the window.
	5. Label the slope with a Text "x/2" at a point just above its bottom left end point.
	6. Add double square(double x) {return x*x;} to the window.
	7. Add a cosine to the window (don't write a new function).
	8. Make the cosine blue.
	9. Write a function sloping_cos() that adds a cosine to slope() (as defined above)
	and add it to the window.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

double one(double x)
{
	return 1;
}

// -----------------------------------------------------------------------------

double slope(double x)
{
	return x/2;
}

// -----------------------------------------------------------------------------

double square(double x)
{
	return x * x;
}

// -----------------------------------------------------------------------------

double sloping_cos(double x)
{
	return cos(x) + slope(x);
}


// -----------------------------------------------------------------------------

int main()
{
	const int xmax = 600;
	const int ymax = 600;
	const int yorigin = ymax / 2;
	const int xorigin = xmax / 2;
	const Point origin{ double(xorigin), double(yorigin) };

	const int axisLength = 400;
	const int notches = 400 / 20;

	const double xscale = 20;
	const double yscale = 20;

	double rangeMin = -10;
	double rangeMax = 11;

	Simple_window win{ Point{100,100}, xmax, ymax, "Function Graphs - Drill 2-9" };

	// -----------------------------------------------------------------------------
	
	Axis xaxis(Axis::x, Point(100, yorigin), axisLength, notches, "x 1== 20 pixels");
	win.attach(xaxis);
	Axis yaxis(Axis::y, Point(xorigin, axisLength + 100), axisLength, notches, "y 1 == 20 pixels");
	win.attach(yaxis);

	// -----------------------------------------------------------------------------

	//Drill 2-1 Function f_one{ one, double(rangeMin), double(rangeMax), origin, notches };
	Function f_one{ one, rangeMin, rangeMax, origin, axisLength, xscale, yscale };
	f_one.set_color(Color::coral);
	win.attach(f_one);

	// -----------------------------------------------------------------------------

	Function f_slope{ slope, rangeMin, rangeMax, origin, axisLength, xscale, yscale };
	f_slope.set_color(Color::green);
	win.attach(f_slope);

	Graph_lib::Text slope_text{ Point{f_slope.point(0).x, f_slope.point(0).y - 10}, "x/2" };
	slope_text.set_color(Color::dark_green);
	win.attach(slope_text);

	// -----------------------------------------------------------------------------

	Function f_square{ square, rangeMin, rangeMax, origin, axisLength, xscale, yscale };
	f_square.set_color(Color::blue);
	win.attach(f_square);

	// -----------------------------------------------------------------------------

	Function f_cos{ cos, rangeMin, rangeMax, origin, axisLength, xscale, yscale };
	f_cos.set_color(Color::cyan);
	win.attach(f_cos);

	// -----------------------------------------------------------------------------

	Function f_slopecos{ sloping_cos, rangeMin, rangeMax, origin, axisLength, xscale, yscale };
	f_slopecos.set_color(Color::pink);
	win.attach(f_slopecos);

	// -----------------------------------------------------------------------------

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
