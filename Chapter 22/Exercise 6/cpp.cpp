// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 22 - Exercise 6

	For each language mentioned in this chapter, look at a popular textbook and 
	see what is used as the first complete program. Write that program in all of 
	the other languages. Warning: This could easily be a 100-program project.

	The exercise I chose is Chapter 3 - Exercise 2:
	"Write a program in C++ that converts from miles to kilometres"

	C++
	Built and written using Visual Studio Community 2019 on Windows 10.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

bool checkQuit()
{
	cout << "Quit? y / n";
	cout << "\n>> ";
	char ans;
	cin >> ans;
	if (ans == 'y')
		return true;
	else
		return false;
}

// -----------------------------------------------------------------------------

int main()
{
	const double m2k = 1.60934;

	cout << "This program converts miles to kilometers.";

	bool quit = false;
	double miles = 0.0;

	while (!quit)
	{
		cout << "\nMiles To Convert: ";
		cin >> miles;
		cout << "\n>> " << miles * m2k << "km" << endl;
		quit = checkQuit();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
