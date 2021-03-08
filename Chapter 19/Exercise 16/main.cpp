// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 16
/*
	Sometimes, it is desirable that an empty vector be as small as possible. For 
	example, someone might use vector<vector<vector<int>>>  a lot but have most 
	elements vectors empty. Define a vector so that sizeof(vector<int>) == sizeof(int*), 
	that is, so that the vector itself consists only of a pointer to a representation 
	consisting of the elements, the number of elements, and a space pointer.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"
#include "SmallVector.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// -----------------------------------------------------------------------------

void testVector()
{
	SmallVector<int> num;
	num.pushBack(10);
	num.pushBack(10);
	num.pushBack(10);
	num.pushBack(10);
	num.pushBack(10);

	SmallVector<int> num2 = num;	// test copy assignment
	num2.resize(1);				// test resize/reserve
	num2.pushBack(20);		// test pushback/reserve

	num2 = SmallVector<int>(20);	// test move assignment
	for (int i = 0; i < num2.size(); ++i)
		num2[i] = i;			// test operator access
	cout << num2[15];

	SmallVector<int> num3;
	num3.reserve(10);			// test reserve
	for (int i = 0; i < 10; ++i)
		num3.pushBack(i);			// test operator access

	SmallVector<int> num4(num3);	// test copy constructor
	for (int i = 0; i < num4.size(); ++i)
		cout << "Num4: " << num4[i] << ", ";			// test operator access
	cout << endl;

	SmallVector<int> num5(SmallVector<int>(20)); // test move constructor
	for (int i = 0; i < num5.size(); ++i)
		cout << "Num5: " << num5[i] << ", ";			// test operator access
	cout << endl;

	vector<vector<vector<int>>> num6(5);
	SmallVector<SmallVector<SmallVector<int>>> num7(5);

	cout << "Size of SmallVector<int>: " << sizeof(SmallVector<int>) << endl;
	cout << "Size of int pointer: " << sizeof(int*) << endl;
	cout << "Size of num5: " << sizeof(num5) << endl;
	cout << "Size of num6: " << sizeof(num6) << endl;
	cout << "Size of num7: " << sizeof(num7) << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	_CrtMemState s1;
	_CrtMemCheckpoint(&s1);
	testVector();
	_CrtMemState s2;
	_CrtMemCheckpoint(&s2);

	_CrtMemState s3;
	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);

	keep_window_open();
	_CrtDumpMemoryLeaks();		// maps malloc and free, checks for memory leaks
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
