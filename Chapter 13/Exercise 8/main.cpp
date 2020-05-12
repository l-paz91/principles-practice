// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 8
/*
	Define a class Regular_hexagon (a regular hexagon is a six-sided polygon with 
	all sides of equal length). Use the center and the distance from the center 
	point as constructor arguments.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Regular_Hexagon H;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 600, "Exercise 8" };

	H hex(Point{ 100,100 }, 100);
	hex.set_color(Color::black);
	hex.set_fill_color(Color::cyan);
	win.attach(hex);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
