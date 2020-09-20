// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 10
/*
	Provide a program where you can choose among a set of functions (e.g., sin() 
	and log(), provide parameters for those functions, and then graph them.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "FunctionWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	FunctionWindow win{ Point{100,100}, 600, 600, "Chapter 16 - Exercise 10" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
