// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 1
/*
   Define a class Arc, which draws a part of an ellipse. Hint: fl_arc().
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

#include <cmath>

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 600, 600, "Chapter 13 - Exercise 1" };

	Graph_lib::Arc arc(Point{ 100, 100 }, 50, 50, 100, 180);
	arc.set_color(Color::black);
	win.attach(arc);
	win.wait_for_button();

	arc.change_angle(210, 350);
	arc.set_color(Color::red);
	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
