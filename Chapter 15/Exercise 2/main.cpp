// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 15 - Exercise 2
/*
	Define a class Fct that is just like Function except that it stores its 
	constructor arguments. Provide Fct with "reset" operations, so that you can 
	use it repeatedly for different ranges, different functions, etc.
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

	Simple_window win{ Point{100,100}, xmax, ymax, "Function Graphs - Exercise 2" };

	// -----------------------------------------------------------------------------
	
	Axis xaxis(Axis::x, Point(100, yorigin), axisLength, notches, "x 1== 20 pixels");
	win.attach(xaxis);
	Axis yaxis(Axis::y, Point(xorigin, axisLength + 100), axisLength, notches, "y 1 == 20 pixels");
	win.attach(yaxis);

	// -----------------------------------------------------------------------------

	StoredFct f_one{ one, rangeMin, rangeMax, origin, axisLength, xscale, yscale };
	f_one.set_color(Color::coral);
	win.attach(f_one);	
	win.wait_for_button();

	f_one.init(sloping_cos, rangeMin, rangeMax, origin, axisLength, xscale, yscale);
	f_one.set_color(Color::blue);
	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
