// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 8
/*
	Provide a currency converter. Read the conversion rates from a file on startup. 
	Enter an amount in an input window and provide a way of selecting currencies 
	to convert to and from (e.g., a pair of menus).

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "CurrencyWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	CurrencyWindow win{ Point{100,100}, 600, 400, "Chapter 16 - Exercise 8" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
