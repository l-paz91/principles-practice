// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 14
/*
Add an operation to Binary_tree that adds text to a node. You may have to modify 
the design of Binary_tree to implement this elegantly. Choose a way to identify 
a node; for example, you might give a string "lrrlr" for navigating left, right, 
right, left, and right down a binary tree (the root node would match both an 
initial l and r.
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
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 14" };

	BT bt(2, 50, BT::NODE_circle);
	bt.addTextToNode(2, "Top");
	win.attach(bt);

	BT bt2(2, 200, BT::NODE_circle, 5);
	bt2.setLineAsArrow(0, Color::red);
	bt2.addTextToNode(0, "Bottom Left");
	win.attach(bt2);

	BT bt3(3, 350, BT::NODE_square, 2);
	bt3.addTextToNode(1, "Bottom Left Middle");
	bt3.addTextToNode(5, "Middle Right");
	bt3.setLineAsArrow(1, Color::red);
	win.attach(bt3);

	BT bt4(4, 500, BT::NODE_triangle);
	win.attach(bt4);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
