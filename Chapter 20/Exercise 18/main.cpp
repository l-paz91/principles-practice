// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 18

	Define a range-checked iterator for vector (a random-access iterator).

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"


//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

typedef uint32_t uint32;

//--GLOBALS--//

// -----------------------------------------------------------------------------

void fct()
{
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

	vector<int>::CheckedIt checkedIt(&v);

	checkedIt = v.begin();
	cout << *checkedIt << endl; 	// should print 1

	++checkedIt; ++checkedIt; ++checkedIt;
	cout << *checkedIt << endl;		// should print 4
	--checkedIt;
	cout << *checkedIt << endl;		// should print 3

	// move the iterator outside of v.size()
	checkedIt = v.end();
	//++checkedIt;	// error
	//cout << *checkedIt << endl; // error
}

 // -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	keep_window_open();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
