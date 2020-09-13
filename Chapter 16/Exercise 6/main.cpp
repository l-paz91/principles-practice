// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 6
/*
	Make an "analog clock," that is, a clock with hands that move. You get the 
	time of day from the operating system through a library call. A major part 
	of this exercise is to find the functions that give you the time of day and 
	a way of waiting for a short period of time(e.g., a second for a clock tick) 
	and learn to use them based on the documentation you found. Hint: clock(), 
	sleep().

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "ClockWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	ClockWindow win{ Point{100,100}, 400, 400, "Chapter 16 - Exercise 6" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
