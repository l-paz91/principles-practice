// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 19
/*
	Define a class Star. One parameter should be the number of points. Draw a 
	few stars with differing numbers of points, differing line colours, and 
	differing fill colours.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Star S;


// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 19" };
	
	S s(Point(200, 300), 200, 100, 100, 5);
	s.set_fill_color(Color::cyan);
	win.attach(s);

	S s1(Point(100, 100), 60, 30, 0, 4);
	s1.set_fill_color(Color::yellow);
	win.attach(s1);

	S s2(Point(400, 120), 120, 20, 0, 17);
	s2.set_fill_color(Color::red);
	win.attach(s2);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
