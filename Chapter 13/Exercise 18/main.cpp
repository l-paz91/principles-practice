// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 18
/*
	Define a class Poly that represents a polygon but checks that its points 
	really do make a polygon in its constructor. Hint: You'll have to supply the 
	points to the constructor.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Poly P;


// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 18" };

	P p{ Point(100, 100), Point(400, 100), Point(400, 400), Point(100, 400), Point(100, 100) };
	p.set_color(Color::cyan);
	p.set_fill_color(Color::dark_cyan);
	win.attach(p);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
