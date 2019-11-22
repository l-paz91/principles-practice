// -----------------------------------------------------------------------------
//
// C9 - Exercise 8
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "PatronClass.h"

// -----------------------------------------------------------------------------

int main()
{
	//book testing
	Book lotr;
	Book ecpp;

	//these should fail
	lotr.createBook("32-32-32-jh", "Lord of the Things", "J.R.R Tolkien", 1954, Genre::children, false);
	lotr.createBook("32-gg-32-X", "Lord of the DingWings", "J.R.R Tolkien", 1954, Genre::children, false);
	lotr.createBook("32-32-32-X", "Lord Of The Chicken Wings", "J.R.R Tolkien", 3000, Genre::children, false);
	lotr.createBook("32-32-32-X", "Lord Of The Pings", "J.R.R Tolkien", 1759, Genre::children, false);

	//this should pass
	lotr.createBook("32-32-32-X", "Lord Of The Rings", "J.R.R Tolkien", 1954, Genre::children, false);
	lotr.setCheckedOut(true);
	ecpp.createBook("0-201-61562-2", "Exceptional C++", "Herb Sutter", 2000, Genre::nonfiction, false);

	cout << lotr;
	cout << ecpp;

	if (lotr == ecpp)
		cout << "This is the same book." << endl;
	else
		cout << "This is not the same book." << endl;

	//patron testing
	Patron user1("Theodore Logan");
	Patron user2("John Wick");

	user2.setFees(0.6);

	cout << user1;
	cout << user2;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
