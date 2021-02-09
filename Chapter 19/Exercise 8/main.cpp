// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 8
/*
	Implement an allocator (section 19.3.7) using the basic allocation functions 
	malloc() and free() (appendix B.11.4). Get vector as defined by the end of 
	section 19.4 to work for a few simple test cases. Hint: Look up "placement new" 
	and "explicit call of destructor" in a complete C++ reference.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"
#include "MyVector.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// -----------------------------------------------------------------------------

void IntVec()
{
	MyVector<int> num;
	num.pushBack(10);
	num.pushBack(10);
	num.pushBack(10);
	num.pushBack(10);
	num.pushBack(10);

	MyVector<int> num2 = num;	// test copy assignment
	num2.resize(1);				// test resize/reserve
	num2.pushBack(20);			// test pushback/reserve

	num2 = MyVector<int>(20);	// test move assignment
	for (int i = 0; i < num2.size(); ++i)
		num2[i] = i;			// test operator access
	cout << num2[15];

	MyVector<int> num3;
	num3.reserve(10);			// test reserve
	for (int i = 0; i < 10; ++i)
		num3.pushBack(i);			// test operator access

	MyVector<int> num4(num3);	// test copy constructor
	for (int i = 0; i < num4.size(); ++i)
		cout << "Num4: " << num4[i] << ", ";			// test operator access
	cout << endl;

	MyVector<int> num5(MyVector<int>(20)); // test move constructor
	for (int i = 0; i < num5.size(); ++i)
		cout << "Num5: " << num5[i] << ", ";			// test operator access
	cout << endl;
}

// -----------------------------------------------------------------------------

void StringVec()
{
	MyVector<string> str;
	str.pushBack("apple");
	str.pushBack("banana");
	str.pushBack("coconut");
	str.pushBack("dragonfruit");
	str.pushBack("elderberry");

	MyVector<string> str2 = str;	// test copy assignment
	str2.resize(1);				// test resize/reserve
	str2.pushBack("Fig");			// test pushback/reserve

	str2 = MyVector<string>(20);	// test move assignment
	for (int i = 0; i < str2.size(); ++i)
		str2[i] = "Grapes";			// test operator access
	cout << str2[15] << endl;

	MyVector<string> str3;
	str3.reserve(10);			// test reserve
	for (int i = 0; i < 10; ++i)
		str3.pushBack(string("Hackberry"));			// test operator access

	MyVector<string> str4(str3);	// test copy constructor
	for (int i = 0; i < str4.size(); ++i)
		cout << "Str4: " << str4[i] << ", ";			// test operator access
	cout << endl;

	MyVector<string> str5(MyVector<string>(20));		// test move constructor
	for (int i = 0; i < str5.size(); ++i)
		cout << "str5: " << str5[i] << ", ";			// test operator access
	cout << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	IntVec();
	StringVec();

	keep_window_open();
	_CrtDumpMemoryLeaks();		// maps malloc and free, checks for memory leaks
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
