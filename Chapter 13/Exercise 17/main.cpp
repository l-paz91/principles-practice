// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 17
/*
	Do the previous exercise, but using hexagons of a few different colours.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// please use graph.h from exercise 15
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::RightTriangle RT;
typedef Graph_lib::Regular_Hexagon H;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 17" };

	vector<H> v_h;
	H::hexagonTile(v_h, 253, 50, x_max(), Point(0, 0));

	for (int i = 0; i < v_h.size(); ++i)
		win.attach(v_h[i]);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
