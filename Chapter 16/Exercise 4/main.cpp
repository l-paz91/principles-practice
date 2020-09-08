// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 4
/*
	Make a menu with items that make a circle, a square, an equilateral triangle, 
	and a hexagon, respectively. Make an input box (or two) for giving a coordinate 
	pair, and place the shape made by pressing a menu item at that coordinate. 
	Sorry, no drag and drop.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "PolygonWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	PolygonWindow win{ Point{100,100}, 600, 400, "Chapter 16 - Exercise 4" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
