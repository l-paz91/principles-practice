// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 9
/*
	Modify the calculator from Chapter 7 to get its input from an input box and 
	return its results in an output box.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "CalculatorWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	CalculatorWindow win{ Point{100,100}, 600, 400, "Chapter 16 - Exercise 9" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
