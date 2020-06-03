// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 8
/*
	Define a Group to be a container of Shapes with suitable operations applied 
	to the various members of the Group. Hint: Vector_ref. Use a Group to define 
	a checkers (droughts) board where pieces can be moved under program control.
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Group G;
// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 8" };

	G board;
	win.attach(board);
	win.wait_for_button();

	board.moveDarkPiece(G::MoveDir::NorthEast, 2);
	win.wait_for_button();

	board.moveLightPiece(G::MoveDir::SouthWest, 11);
	win.wait_for_button();

	board.moveDarkPiece(G::MoveDir::NorthWest, 2);
	win.wait_for_button();

	board.moveLightPiece(G::MoveDir::SouthEast, 9);
	board.removePiece(2);
	board.moveLightPiece(G::MoveDir::SouthEast, 9);
	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
