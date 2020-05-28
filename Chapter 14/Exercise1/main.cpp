// -----------------------------------------------------------------------------
//
// Chapter 14 - Exercise 1
/*
	Define two classes Smiley and Frowny, which are both derived from class Circle 
	and have two eyes and a mouth. Next, derive classes from Smiley and Frowny 
	which add an appropriate hat to each.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::SmileyHat S;
typedef Graph_lib::FrownyHat F;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 1" };
	
	S smiley(Point{ 200,200 }, 100);
	smiley.set_color(Color::black);
	smiley.set_fill_color(Color::yellow);
	win.attach(smiley);

	F frowny(Point{ 400,400 }, 100);
	frowny.set_color(Color::black);
	frowny.set_fill_color(Color::yellow);
	win.attach(frowny);


	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
