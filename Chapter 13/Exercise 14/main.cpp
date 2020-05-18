// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 14
/*
	Define a right triangle class. Make an octagonal shape out of eight right 
	triangles of different colours.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::RightTriangle RT;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 14" };

	vector<RT> v_rt{
		RT(Point(300, 0), Point(100, 200), Point(300, 400), Color::black),
		RT(Point(100, 200), Point(100, 400), Point(300, 400), Color::blue),
		RT(Point(100, 400), Point(300, 600), Point(300, 400), Color::cyan),
		RT(Point(300, 0), Point(300, 600), Point(500, 0), Color::green),
		RT(Point(300, 600), Point(500, 600), Point(500, 0), Color::red),
		RT(Point(500, 0), Point(700, 200), Point(500, 400), Color::white),
		RT(Point(700, 200), Point(700, 400), Point(500, 400), Color::yellow),
		RT(Point(500, 400), Point(500, 600), Point(700, 400), Color::dark_magenta)
	};

	for (int i = 0; i < v_rt.size(); ++i)
		win.attach(v_rt[i]);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
