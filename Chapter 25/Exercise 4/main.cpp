// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 25 - Exercise 4

	Add the bitwise logical operators &, |, ^, and ~ to the calculator from chapter 7.

	I'm using a cleaned up version of my code from C7 - Exercise 9:
	https://github.com/l-paz91/principles-practice/blob/master/Chapter%207/Exercise%209

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Calculator.h"

// -----------------------------------------------------------------------------

int main()
{
	Calculator calculator;

	//pre-defined names
	calculator.defineName("k", 1000, true);
	calculator.calculate();

	cout << "\n\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
