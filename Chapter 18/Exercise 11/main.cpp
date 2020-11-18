// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 18 - Exercise 11
/*
	Look up (e.g., on the web) skip list and implement that kind of list. 
	This is not an easy exercise.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Skiplist.h"

// -----------------------------------------------------------------------------

vector<Node> v(100);

int main()
{
	Skiplist sList(3);
	sList.insert(4);
	sList.insert(7);
	sList.insert(2);

	sList.remove(7);

	Node* findByValue = sList.findByValue(4);
	cout << findByValue->mValue << endl;

	Node* findByIndex = sList.findByValue(sList.mSize-1);
	cout << findByIndex->mValue << endl << endl;

	sList.insert(10);
	sList.insert(5);
	sList.insert(12);
	sList.print();

	for (int i = 0; i < 100; ++i)
	{
		sList.insert(i + i + 1);
	}

	cout << endl;
	sList.print();

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
