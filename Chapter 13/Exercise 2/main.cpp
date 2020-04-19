// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 2
/*
   Draw a box with rounded corners. Define a class Box, consisting of four lines 
   and four arcs.
   
   Note - when you change the round amount, the size of the rectangle will change 
   as the radius is being directly changed. In order to preserve rectangle size, 
   the amount of points added along the arc need to be reduced instead.
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

	Graph_lib::Box box(Point{ 100,100 }, 300, 200, 100);
	box.set_color(Color::black);
	win.attach(box);
	win.wait_for_button();

	box.change_roundAmount(20);
	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
