// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 5
/*
	Write a program that draws a shape of your choice and moves it to a new point
	each time you click "Next". The new point should be determined by a co-ordinate 
	pair read from an input stream.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "PolygonWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	PolygonWindow win{ Point{100,100}, 600, 400, "Chapter 16 - Exercise 5" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
