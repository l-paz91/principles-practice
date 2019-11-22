// -----------------------------------------------------------------------------
//
// C9 - Exercise 9
//
// And these exercise are finally done. I've started them a million times as I did them
// in a super data-oriented style however it didn't allow for gradual implementation
// like the exercises wanted you to do. I'm not a big fan of how this is done as I think
// it's pretty wasteful to create books and patrons and then add them to the library.
// the library should manage books and patrons itself.
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "LibraryClass.h"

// -----------------------------------------------------------------------------

int main()
{
	Library library;

	//book testing
	Book lotr;
	Book ecpp;
	lotr.createBook("32-32-32-X", "Lord Of The Rings", "J.R.R Tolkien", 1954, Genre::children, false);
	ecpp.createBook("0-201-61562-2", "Exceptional C++", "Herb Sutter", 2000, Genre::nonfiction, false);

	//patron testing
	Patron user1("Theodore Logan");
	Patron user2("John Wick");

	//check out a book
	library.addBook(lotr);
	library.addBook(ecpp);
	library.addPatron(user1);
	library.addPatron(user2);
	library.checkOutBook(lotr, user1);

	cout << "Is " << lotr.getTitle() << " checked out: " << boolalpha << lotr.isCheckedOut() << endl;
	cout << "Is " << ecpp.getTitle() << " checked out: " << boolalpha << ecpp.isCheckedOut() << endl;

	cout << library.getTransactions();

	user1.setFees(1.10);
	library.modifyPatron(user1);

	cout << "Users with fees: " << endl;
	vector<string> usersWithFees = library.getPatronsWithFees();
	for (string s : usersWithFees)
		cout << s << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
