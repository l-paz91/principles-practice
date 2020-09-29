// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 17 - Exercise 5
/*
	Write a function, char* findx(const char* s, const char* x), that finds the 
	first occurance of the C-style string x in s.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

char* findx(const char* s, const char* x)
{
	char* start = const_cast<char*>(s);
	for (; *start != 0; ++start)
	{
		if (*start == *x)
			return start;
	}
	return 0;
}

// -----------------------------------------------------------------------------

int main()
{
	string s = "hello, world";
	const char* c;
	c = findx(s.c_str(), "o");

	cout << c << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
