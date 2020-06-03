// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 10
/*
	Define a class Pseudo_window that looks as much like a Window as you can make 
	it without heroic efforts. It should have rounded corners, a label, and control 
	icons. Maybe you could add some "fake contents", such as an image. It need 
	not actually do anything. It is acceptable (and indeed recommended) to have 
	it appear within a Simple_window.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Pseudo_window RO;
// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 10" };

	RO ro("An app on your PC needs the following Windows feature:");
	win.attach(ro);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
