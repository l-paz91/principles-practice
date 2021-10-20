// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 15

	Provide a GUI for the program from the previous exercise.
	Please note that some words appear longer or shorter than they actually are
	due to replacing punctuation with whitespace. This is also why the shortest
	word is a space.

	NOTE - This solution uses FLTK files from the end of Chapter 16 and 19.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "FileQueryWindow.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	FileQueryWindow fqw(Point(100, 100), 600, 400, "Chapter 21 - Exercise 15");

	return 	gui_main();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
