// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 3
/*
	Define a class Arrow, which draws a line with an arrowhead.
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
	Simple_window win{ Point{100,100}, 600, 600, "Chapter 13 - Exercise 3" };

	Point p(200, 200);
	Point p2(500, 200);
	
	Graph_lib::Arrow arrow(p, Point{ 200,500 }, 100);
	arrow.set_color(Color::black);
	arrow.set_fill_color(Color::yellow);
	win.attach(arrow);	
	win.wait_for_button();

	arrow.moveArrow(p, Point{ 500, 400 });
	win.wait_for_button();

	arrow.moveArrow(p, Point{ 500, 200 });
	win.wait_for_button();

	arrow.moveArrow(p2, p);
	win.wait_for_button();

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
