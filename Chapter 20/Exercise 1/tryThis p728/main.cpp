// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 1

	If you haven't already, do all the 'Try This' exercises in the chapter.

	p728 - The standard library vector doesn't provide push_front(). Why not?
	Implement push_front for vector and compare it to push_back().
	
	// my change is in std_lib_facilities on line 100

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

int main()
{
	vector<int> n{ 1,2,3,4,5,6,7,9,10 };
	n.push_front(0);

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
