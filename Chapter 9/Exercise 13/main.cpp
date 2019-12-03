// -----------------------------------------------------------------------------
//
// C9 - Exercise 13
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "RationalClass.h"

// -----------------------------------------------------------------------------

int main()
{
	Rational r1(1, 1);
	Rational r2(1, 1);
	Rational temp(1, 1);

	//addition
	r1.set(1, 2);
	r2.set(1, 4);	
	temp = r1 + r2;
	cout << temp;	//should be 3/4
	cout << " as decimal: " << temp.rationalToDouble() << endl;
	r1.set(1, 3);
	r2.set(1, 5);
	temp = r1 + r2;
	cout << temp;	//should be 8/15
	cout << " as decimal: " << temp.rationalToDouble() << endl;

	//subtraction
	r1.set(3, 4);
	r2.set(1, 4);
	temp = r1 - r2;
	cout << temp;	//should be 1/2
	cout << " as decimal: " << temp.rationalToDouble() << endl;
	r1.set(1, 2);
	r2.set(1, 6);
	temp = r1 - r2;
	cout << temp;	//should be 1/3
	cout << " as decimal: " << temp.rationalToDouble() << endl;
						
	//multiplication
	r1.set(1, 2);
	r2.set(2, 5);
	temp = r1 * r2;
	cout << temp;	//should be 1/5
	cout << " as decimal: " << temp.rationalToDouble() << endl;
	r1.set(3, 1);
	r2.set(2, 9);
	temp = r1 * r2;
	cout << temp;	//should be 2/3
	cout << " as decimal: " << temp.rationalToDouble() << endl;

	//division
	r1.set(2, 3);
	r2.set(5, 1);
	temp = r1 / r2;
	cout << temp;	//should be 2/15
	cout << " as decimal: " << temp.rationalToDouble() << endl;
	r1.set(3, 1);
	r2.set(1, 4);
	temp = r1 / r2;
	cout << temp;	//should be 12
	cout << " as decimal: " << temp.rationalToDouble() << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
