// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 14, 15
/*
	14 - Provide a GUI interface and a bit of graphical output to the "Hunt the Wumpus" 
	game from the exercises in Chapter 18. Take the input in an input box and 
	display a map of the part of the cave currently known to the player in a window.

	15 - Modify the program from the previous exercise to allow the user to mark 
	rooms based on knowledge and guesses, such as "maybe bats" and "bottomless pit."

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "WumpusWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	// set seed for random
	srand(static_cast<unsigned int>(time(NULL)));

	WumpusWindow win{ Point{100,100}, 600, 600, "Hunt the Wumpus - C19 E14" };
	win.changeBGcolour(42, 43, 46);
	win.playGame();

	return 	gui_main();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
