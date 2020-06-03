// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 8
/*
	Define a class Octagon to be a regular octagon. Write a test that exercises 
	all of its functions (as defined by you or inherited from shape).
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Regular_Octagon RO;
// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 8" };

	//test first constructor
	RO ro1(Point(100, 100), 50);
	//test set outline colour
	ro1.set_color(Color::pink);
	//test set fill color
	ro1.set_fill_color(Color::cream);
	//test set line style
	ro1.set_style(Line_style(Line_style::dashdotdot, 10));
	//test number of points
	if (ro1.number_of_points() != 8)
		error("Should have 8 points");
	//test returning a point
	if (ro1.point(2) != Point{ 100,150 })
		error("Should have returned the correct point");
	win.attach(ro1);
	win.wait_for_button();

	//test move
	ro1.move(300, 300);
	//set point has been disabled for a regular octagon
	//test line visibility
	ro1.setLineVisibility(false);
	win.wait_for_button();
	
	//test fill visibility
	ro1.setFillVisibility(false);
	win.wait_for_button();

	ro1.setLineVisibility(true);
	ro1.setFillVisibility(true);

	//get point direction has not been defined for an octagon
	//add() has been disabled

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
