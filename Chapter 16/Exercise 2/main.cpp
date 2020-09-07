// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 2
/*
	Make a window (based on My_window) with a 4-by-4 checkerboard of square buttons. 
	When pressed, a button performs a simple action, such as printing its coordinates 
	in an output box, or turns a slightly different colour (until another button 
	is pressed).
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "CheckerboardWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	CheckerboardWindow win{ Point{100,100}, 300, 300, "Chapter 16 - Exercise 2" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
