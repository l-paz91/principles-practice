// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 11
/*
	Define a Binary_tree class derived from Shape. Give the number of levels as a 
	parameter (levels == 0) means no nodes, levels == 1 means one node, levels == 2 
	means one top node with two sub-nodes, levels == 3 means one top node with two 
	sub-nodes each with two sub-nodes, etc). Let a node be represented by a small 
	circle. Connect the nodes by lines (as is conventional). P.S. In computer 
	science, trees grow downward from a top node (amusingly, but logically, often 
	called the root).
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

	BT bt(1, 50);
	win.attach(bt);

	BT bt2(2, 100);
	win.attach(bt2);

	BT bt3(3, 200);
	win.attach(bt3);

	BT bt4(4, 350);
	win.attach(bt4);

	BT bt5(5, 450);
	win.attach(bt5);

	//BT bt6(6, 600);
	//win.attach(bt6);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
