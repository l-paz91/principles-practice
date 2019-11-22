// -----------------------------------------------------------------------------
//
// C9 - Exercise 6
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "BookClass.h"

// -----------------------------------------------------------------------------

int main()
{
	Book lotr;
	Book ecpp;

	//these should fail
	lotr.createBook("32-32-32-jh", "Lord of the Things", "J.R.R Tolkien", 1954, false);
	lotr.createBook("32-gg-32-X", "Lord of the DingWings", "J.R.R Tolkien", 1954, false);
	lotr.createBook("32-32-32-X", "Lord Of The Chicken Wings", "J.R.R Tolkien", 3000, false);
	lotr.createBook("32-32-32-X", "Lord Of The Pings", "J.R.R Tolkien", 1759, false);

	//this should pass
	lotr.createBook("32-32-32-X", "Lord Of The Rings", "J.R.R Tolkien", 1954, false);
	lotr.setCheckedOut(true);
	ecpp.createBook("0-201-61562-2", "Exceptional C++", "Herb Sutter", 2000, false);

	cout << lotr;
	cout << ecpp;

	if (lotr == ecpp)
		cout << "This is the same book." << endl;
	else
		cout << "This is not the same book." << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
