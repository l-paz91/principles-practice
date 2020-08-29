// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Drills 1, 2, 3, 4
/*
	1. Make a completely new project with linker settings for FLTK (as described 
	in Appendix D).
	2. Using the facilities of Graph_lib, type in the line-drawing program from 
	section 16.5 and get it to run.
	3. Modify the program to use a pop-up menu as described in section 16.7 and 
	get it to run.
	4. Modify the program to have a second menu for choosing line styles and get 
	it to run.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "GUI.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	Lines_window win{ Point{100,100}, 600, 400, "lines" };

	return gui_main();
	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
