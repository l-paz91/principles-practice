// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 16
/*
	Define a class Controller with four virtual functions on(), off(), set_level(int), 
	and show(). Derive at least two classes from Controller. One should be a 
	simple test class where show() prints out whether the class is set to on or 
	off and what is the current level. The second derived class should somehow 
	control the line color of a Shape; the exact meaning of "level" is up to you. 
	Try to find a third "thing" to control with such a Controller class.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Binary_tree BT;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 16" };

	//test class prints out if class is on or off + level
	Test_Controller tc;
	tc.on();
	Graph_lib::Text t = tc.show();
	t.set_color(Color::black);
	win.attach(t);
	win.wait_for_button();

	tc.off();
	t = tc.show();
	win.attach(t);
	win.wait_for_button();

	//controls the line colour of a shape
	Graph_lib::Rectangle r(Point(100, 100), 100, 100);
	Line_Controller lc(&r);
	win.attach(r);
	win.wait_for_button();

	lc.set_level(Color::cyan);
	win.wait_for_button();

	//moves a shape??
	Graph_lib::Circle c(Point(200, 100), 10);
	c.set_color(Color::dark_magenta);
	Move_Controller mc(&c);
	win.attach(c);
	win.wait_for_button();

	mc.set_level(25);
	win.wait_for_button();

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
