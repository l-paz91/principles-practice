// -----------------------------------------------------------------------------
//
// C9 - Exercise 5
//
// I struggled with this because work has me constantly thinking about data now 
// instead of objects. Trying to just imagine 'a book' and the operations it may
// need proved more difficult than thinking about what data a library would need
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "BookClass.h"

// -----------------------------------------------------------------------------

int main()
{
	Book lotr;

	//these should fail
	lotr.createBook("32-32-32-jh", "Lord of the Things", "J.R.R Tolkien", 1954, false);
	lotr.createBook("32-gg-32-X", "Lord of the DingWings", "J.R.R Tolkien", 1954, false);
	lotr.createBook("32-32-32-X", "Lord Of The Chicken Wings", "J.R.R Tolkien", 3000, false);
	lotr.createBook("32-32-32-X", "Lord Of The Pings", "J.R.R Tolkien", 1759, false);

	//this should pass
	lotr.createBook("32-32-32-X", "Lord Of The Rings", "J.R.R Tolkien", 1954, false);
	cout << "Checked out: " << boolalpha << lotr.isCheckedOut() << endl;

	lotr.setCheckedOut(true);
	cout << "Checked out: " << boolalpha << lotr.isCheckedOut() << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
