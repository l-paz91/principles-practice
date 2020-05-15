// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 8
/*
	Tile a part of the window with Regular_hexagons (use at least eight hexagons).
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
	Simple_window win{ Point{100,100}, 800, 600, "Exercise 9" };

	vector<H> hexes; 
	H::hexagonTile(hexes, 10, 50, 500, Point(0, 0));
	for (int i = 0; i < hexes.size(); ++i)
		win.attach(hexes[i]);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
