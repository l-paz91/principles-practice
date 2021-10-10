// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 11

	Provide a GUI interface for entering Orders into files.

	NOTE - This solution uses FLTK files from the end of Chapter 16 and 19.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "OrderWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	OrderWindow ow(Point(100, 100), 600, 400, "Chapter 21 - Exercise 11");

	return 	gui_main();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
