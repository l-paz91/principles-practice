// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 5
/*
	Define a Striped_Rectangle where instead of fill, the rectangle is "filled" 
	by drawing one-pixel-wide horizontal lines across the inside of the rectangle 
	(say, draw every second like that). You may have to play with the width of 
	the lines and the line spacing to get a pattern you like.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Striped_rectangle SR;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 5" };
	
	SR sr(Point{ 50,50 }, 200, 100, 5);
	sr.set_fill_color(Color::pink);
	win.attach(sr);

	SR sr2(Point{ 50,200 }, 400, 50, 10);
	sr2.set_color(Color::red);
	sr2.set_fill_color(Color::coral);
	win.attach(sr2);

	SR sr3(Point{ 300,50 }, 200, 100, 20);
	sr3.set_color(Color::dark_green);
	sr3.set_fill_color(Color::lime);
	win.attach(sr3);

	SR sr4(Point{ 50,300 }, 200, 200, 1);
	sr4.set_color(Color::dark_blue);
	sr4.set_fill_color(Color::blue);
	win.attach(sr4);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
