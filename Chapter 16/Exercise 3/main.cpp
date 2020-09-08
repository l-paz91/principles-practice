// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 16 - Exercise 2
/*
	Place an Image  on top of a Button; move both when the button is pushed. Use 
	this random nuber generator from std_lib_facilities.h to pick a new location 
	for the "image button":

	#include <random>

	inline int_rand_int(int min, int max)
	{
		static default_random_engine ran;
		return uniform_int_distribution<>{min, max}(ran);
	}

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "My_window.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	My_window win{ Point{100,100}, 300, 300, "Chapter 16 - Exercise 3" };

	return gui_main();	
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
