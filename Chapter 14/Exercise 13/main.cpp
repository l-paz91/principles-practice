// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 13
/*
	Modify Binary_tree to take a parameter (or parameters) to indicate what kind 
	of line to use to connect the nodes (e.g., an arrow pointing down or a red 
	arrow pointing up). Note how this exercise and the last use two alternative 
	ways of making a class hierarchy more flexible and useful.
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
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 13" };

	BT bt(2, 50, BT::NODE_circle);
	win.attach(bt);

	BT bt2(2, 200, BT::NODE_circle, 5);
	bt2.setLineAsArrow(0, Color::red);
	win.attach(bt2);

	BT bt3(3, 350, BT::NODE_square, 2);
	bt3.setLineAsArrow(1, Color::red);
	win.attach(bt3);

	BT bt4(4, 500, BT::NODE_triangle);
	win.attach(bt4);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
