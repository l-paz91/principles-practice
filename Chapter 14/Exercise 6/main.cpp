// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 6
/*
	Define a Striped_circle using the technique from Striped_rectangle.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Striped_circle SC;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 6" };
	
	SC sc(Point{ 100,100 }, 100, 20);
	sc.set_color(Color::red);
	win.attach(sc);

	SC sc2(Point{ 350,100 }, 100, 2);
	sc2.set_fill_color(Color::coral);
	sc2.set_color(Color::black);
	win.attach(sc2);

	SC sc3(Point{ 100,350 }, 50, 5);
	sc3.set_fill_color(Color::lime);
	sc3.set_color(Color::black);
	win.attach(sc3);

	SC c(Point{ 200, 200 }, 100, 10);
	c.set_color(Color::black);
	c.set_fill_color(Color::coral);
	win.attach(c);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
