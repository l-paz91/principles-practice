// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 12

	Provide a GUI interface for querying a file of Orders; e.g., "Find all orders
	from Joe," "Find the total value of orders in file Hardware," and "List all
	orders in file Clothing." Hint: First design a non-GUI interface; then, build
	the GUI on top of that.

	NOTE - This solution uses FLTK files from the end of Chapter 16 and 19.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "OrderQueryWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	OrderQueryWindow ow(Point(100, 100), 600, 400, "Chapter 21 - Exercise 12");

	return 	gui_main();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
