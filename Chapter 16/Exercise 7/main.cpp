// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 7
/*
	Using the techniques developed in the previous, make an image of an airplane 
	"fly around" in a window. Have a "Start" and a "Stop" button.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "AnimPlaneWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	AnimPlaneWindow win{ Point{100,100}, 600, 400, "Chapter 16 - Exercise 7" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
