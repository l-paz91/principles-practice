// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 19

	Define a range-checked iterator for list (a bidirectional iterator).

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"
#include "CheckedIterator.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

typedef uint32_t uint32;

//--GLOBALS--//

// -----------------------------------------------------------------------------

void vectorUsingCheckedIterator()
{
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };

	CheckedIterator<vector<int>> checkedIt(&v);

	checkedIt = v.begin();
	cout << *checkedIt << endl; 	// should print 1

	checkedIt += 3;
	cout << *checkedIt << endl;		// should print 4
	--checkedIt;
	cout << *checkedIt << endl;		// should print 3

	checkedIt += 4;
	cout << *checkedIt << endl;		// should print 7

	checkedIt = checkedIt - 2;
	cout << *checkedIt << endl;		// should print 5


	CheckedIterator<vector<int>> checkedIt2(&v);
	checkedIt2 = checkedIt;
	checkedIt2 -= 2;
	checkedIt -= checkedIt2;
	cout << *checkedIt << endl;		// should print 3

	// move the iterator outside of v.size()
	checkedIt = v.end();
	//++checkedIt;	// error
	//cout << *checkedIt << endl; // error
}

// -----------------------------------------------------------------------------

void listUsingCheckedIterator()
{
	list<string> l{ "symbols", "operator", "checkedIterator", "typename", "iterator" };

	CheckedIterator<list<string>> checkedIt(&l);

	checkedIt = l.begin();
	cout << *checkedIt << endl; 	// should print "symbols"

	//checkedIt += 3;				// error - lists can't use arithmetics +, += etc
	++checkedIt; ++checkedIt; ++checkedIt;
	cout << *checkedIt << endl;		// should print "typename"
	--checkedIt;
	cout << *checkedIt << endl;		// should print "checkedIterator"

	CheckedIterator<list<string>> checkedIt2(&l);
	checkedIt2 = checkedIt;
	//--checkedIt2; --checkedIt2; --checkedIt2; // error
}

void fct()
{
	vectorUsingCheckedIterator();
	listUsingCheckedIterator();
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
