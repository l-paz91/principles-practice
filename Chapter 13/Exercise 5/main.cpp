// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 5
/*
	Define the functions from exercise 4 for a Circle and an Ellipse. Place the 
	connection points on or outside the shape but not outside the bounding 
	rectangle.
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
	Simple_window win{ Point{100,100}, 1000, 1000, "Chapter 13 - Exercise 5" };

	Point p(400, 400);
	Point xc(400, 400);

	Graph_lib::Ellipse r(p, 200, 100);
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

	Mark x('x');
	x.add(xc);
	x.set_color(Color::dark_cyan);
	win.attach(x);

	win.wait_for_button();

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
