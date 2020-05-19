// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 15
/*
	"Tile" a window with small right triangles.
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
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 15" };

	vector<RT> v_rt;
	RT::rightTriangleTileWindow(v_rt, 50);

	for (int i = 0; i < v_rt.size(); ++i)
		win.attach(v_rt[i]);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
