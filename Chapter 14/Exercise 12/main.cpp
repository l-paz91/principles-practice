// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 12
/*
	Modify Binary_tree to draw its nodes using a virtual function. Then, derive 
	a new class from Binary_tree that overrides that virtual function to use a 
	different representation for a node (e.g., a triangle).
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
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 12" };

	BT bt(1, 50, BT::NODE_circle);
	win.attach(bt);

	BT bt2(2, 100, BT::NODE_circle);
	win.attach(bt2);

	BT bt3(3, 200, BT::NODE_triangle);
	win.attach(bt3);

	BT bt4(4, 350, BT::NODE_triangle);
	win.attach(bt4);

	BT bt5(5, 450, BT::NODE_square);
	win.attach(bt5);

	BT bt6(6, 600, BT::NODE_square);
	win.attach(bt6);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
