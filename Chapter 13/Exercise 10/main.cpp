// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 10
/*
	Define a class Regular_Polygon. Use the center, the number of sides (>2), 
	and the distance from the center to a corner as constructor arguments.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Regular_polygon P;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 600, "Exercise 10" };

	P poly(Point(70, 70), 70, 12);
	poly.set_color(Color::black);
	poly.set_fill_color(Color::dark_cyan);
	win.attach(poly);

	P poly2(Point(200, 70), 50, 3);
	poly2.set_color(Color::black);
	poly2.set_fill_color(Color::dark_cyan);
	win.attach(poly2);

	P poly3(Point(50, 200), 20, 5);
	poly3.set_color(Color::black);
	poly3.set_fill_color(Color::dark_cyan);
	win.attach(poly3);

	P poly4(Point(170, 190), 80, 7);
	poly4.set_color(Color::black);
	poly4.set_fill_color(Color::dark_cyan);
	win.attach(poly4);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
