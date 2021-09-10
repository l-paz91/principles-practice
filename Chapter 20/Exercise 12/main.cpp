// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 12

	Complete the definition of list from section 20.4.1-2 and get the high() 
	example to run. Allocate a Link to represent one past the end.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MyList.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

typedef uint32_t uint32;

//--GLOBALS--//

// -----------------------------------------------------------------------------

template<typename Iter>
Iter high(Iter pFirst, Iter pLast)
{
	// return an iterator to the element in [pFirst, pLast) that has the highest value
	Iter high = pFirst;
	for (Iter p = pFirst; p != pLast; ++p)
		if (*high < *p)
			high = p;
	return high;
}

// -----------------------------------------------------------------------------

void fct()
{
	MyList<int> myList;

	for (int x; cin >> x; )
		myList.pushFront(x);

	MyList<int>::Iterator it = high(myList.begin(), myList.end());
	cout << "The highest value in the list is: " << *it << endl;
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
