// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 1
/*
	Make a My_window that's a bit like Simple_window except that it has two buttons,
	next and quit.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "My_window.h"

// -----------------------------------------------------------------------------

int main()
{
	My_window win{ Point{100,100}, 600, 400, "Chapter 16 - Exercise 1" };

	Graph_lib::Regular_polygon r1{ Point{100,100}, 75, 4 };
	r1.set_fill_color(Color::blue);
	win.attach(r1);
	win.waitForNext();

	Graph_lib::Regular_polygon r2{ Point{300,300}, 75, 4 };
	r2.set_fill_color(Color::green);
	win.attach(r2);
	win.waitForNext();

	return gui_main();
	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
