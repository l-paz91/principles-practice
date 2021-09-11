// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 14

	Define a singly-linked list, slist, in the style of std::list. Which operations 
	from list could you reasonably eliminate from slist because it doesn't have 
	back pointers?

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "SList.h"

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

void printList(SList<int>& l)
{
	for (int i : l)
		cout << i << ", ";
	cout << endl;
}

// -----------------------------------------------------------------------------

void fct()
{
	SList<int> myList;

	cout << "Is list empty? " << boolalpha << myList.empty() << endl;

	cout << "Please enter numbers:";
	for (int x; cin >> x; )
		myList.pushFront(x);

	SList<int>::Iterator it = high(myList.begin(), myList.end());
	cout << "The highest value in the list is: " << *it << endl;
	int f = myList.front();
	SList<int>::Iterator back = myList.back();
	int b = *back;
	cout << "Front: " << f << "       |  Back : " << b << endl;
	cout << "Is list empty? " << myList.empty() << endl;

	myList.clear();
	cout << "Is list empty? " << myList.empty() << endl;

	myList.pushFront(54);
	myList.pushFront(5);
	myList.pushFront(1000);
	myList.pushFront(1);
	it = high(myList.begin(), myList.end());
	myList.insertAfter(it, 999);
	printList(myList);
	
	myList.eraseAfter(it);
	printList(myList);

	myList.popFront();
	printList(myList);

	myList.resize(10);
	printList(myList);

	SList<int> myList2;
	myList2.pushFront(12);
	myList2.pushFront(567);
	myList2.pushFront(4);
	myList2.pushFront(37);

	cout << "MyList1: "; printList(myList);
	cout << "MyList2: "; printList(myList2);
	cout << "Swapping...." << endl;
	myList.swap(myList2);
	cout << "MyList1: "; printList(myList);
	cout << "MyList2: "; printList(myList2);
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
