// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 2
/*
   Draw a box with rounded corners. Define a class Box, consisting of four lines 
   and four arcs.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 600, 600, "Chapter 13 - Exercise 2" };

	Point p(50, 50);
	
	Graph_lib::Box box(p, 300, 200, 20);
	box.set_color(Color::magenta);
	box.set_fill_color(Color::white);
	win.attach(box);

	Graph_lib::Box box2(p, 300, 200, 100);
	box2.set_color(Color::black);
	box2.set_fill_color(Color::green);
	win.attach(box2);

	win.wait_for_button();

	box2.change_roundAmount(300); //will error
	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
