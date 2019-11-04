// -----------------------------------------------------------------------------
//
// C9 - Exercise 7
//
// -----------------------------------------------------------------------------

#include "BookClass.h"

// -----------------------------------------------------------------------------

int main()
{
	//create a pointer to the single instance class to prevent using Books::getInstance() every time
	Books& booksPtr = Books::getInstance();

	booksPtr.add("Lord of the Rings", "J.R.R Tolkien", "32-32-32-H", 1954, Genre::children);
	booksPtr.checkOut("32-32-32-H");

	//these should not be registered
	booksPtr.add("Lord of the Things", "J.T.T Trollkien", "BH-32-32-8", 1954, Genre::children);
	booksPtr.add("Lord of the DingWings", "J.T.T Trollkien", "45613-4564862-3-L", 3000, Genre::children);

	cout << "\n# Books Registered: " << booksPtr.getBooks().size() << endl;
	cout << "# Books Checked Out: " << booksPtr.getCBooks().size() << endl;

	booksPtr.checkIn("32-32-32-H");
	cout << "# Books Checked Out: " << booksPtr.getCBooks().size() << endl;

	cout << "\n" << booksPtr.getBook("32-32-32-H");

	//remove a book
	booksPtr.remove("32-32-32-H");
	cout << "\n# Books Registered: " << booksPtr.getBooks().size() << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
