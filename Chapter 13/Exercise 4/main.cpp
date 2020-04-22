// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 4
/*
	Define functions n(), s(), e(), w(), center(), ne(), se(), sw(), and nw(). 
	Each takes a Rectangle argument and returns a Point. These functions define 
	"connection points" on and in the rectangle. For example, nw(r) is the 
	northwest (top left) corner of a Rectangle called r.
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
	Simple_window win{ Point{100,100}, 600, 600, "Chapter 13 - Exercise 4" };

	Point p(100, 100);

	Graph_lib::Rectangle r(p, 100, 100);
	r.set_color(Color::black);
	win.attach(r);

	Mark d('x');
	d.add(r.getPointDirection(Shape::NW));
	d.add(r.getPointDirection(Shape::N));
	d.add(r.getPointDirection(Shape::NE));
	d.add(r.getPointDirection(Shape::E));
	d.add(r.getPointDirection(Shape::SE));
	d.add(r.getPointDirection(Shape::S));
	d.add(r.getPointDirection(Shape::SW));
	d.add(r.getPointDirection(Shape::W));
	d.add(r.getPointDirection(Shape::CENTER));
	d.set_color(Color::red);
	win.attach(d);

	win.wait_for_button();

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
