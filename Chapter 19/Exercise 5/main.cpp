// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 5
/*
	Define a class Int having a single member of class int. Define constructors, 
	assignment, and operators +, -, *, / for it. Test it, and improve its design 
	as needed (e.g., define operators << and >> for convenient I/O).
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "IntClass.h"

// -----------------------------------------------------------------------------


int main()
{
	Int myInt = 2;
	cout << myInt << endl;

	cout << "New int: "; cin >> myInt;
	cout << myInt << endl;

	myInt = myInt + 5;
	cout << myInt << endl;

	myInt += 5;
	cout << myInt << endl;

	myInt = myInt * 10;
	cout << myInt << endl;

	myInt *= 10;
	cout << myInt << endl;

	myInt = myInt / 10;
	cout << myInt << endl;

	myInt /= 10;
	cout << myInt << endl;

	myInt = myInt - 100;
	cout << myInt << endl;

	myInt -= 100;
	cout << myInt << endl;

	Int myInt2 = 10;
	myInt = myInt2;
	cout << myInt << endl;

	myInt = myInt + myInt2;
	cout << myInt << endl;

	myInt = myInt - myInt2;
	cout << myInt << endl;

	myInt = myInt * myInt2;
	cout << myInt << endl;

	myInt = myInt / myInt2;
	cout << myInt << endl;

	myInt += myInt2;
	cout << myInt << endl;

	myInt -= myInt2;
	cout << myInt << endl;

	myInt *= myInt2;
	cout << myInt << endl;

	myInt /= myInt2;
	cout << myInt << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
