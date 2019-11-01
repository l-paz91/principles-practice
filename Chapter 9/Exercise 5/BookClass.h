// ---------------------------------------------------------------------------//
//BookClass.h
// ---------------------------------------------------------------------------//
#ifndef _BOOKCLASS_H_

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

/*
	The problem with this exercise is it gives the impression that there is only
	1 book. You will need to create a new book class every time you want to add a
	new book to your library. This is, what I believe anyway, to be the main
	problem with Object Orientated programming as, if you can have one of the 
	object, you will more than likely have more of them later on. This can become
	a hindrance to performance. Therefore, I have decided to solve this using a 
	Data Orientated approach.
*/

class Books
{
public:
	static Books& getInstance();
	~Books() {}								//destructor

	bool add(string title, string author, string isbn, int crDate);
	bool remove(string isbn);
	void checkOut();
	void checkIn();

private:
	Books() {}								//private constructor to prevent more than one class being created
	Books(const Books&) {}					//private copy constructor to prevent copying by construction
	Books& operator=(const Books&) {}		//private copy constructor to prevent copying by assignment

	struct Book
	{
		Book(string isbn, string title, string author, int crDate, bool checkout)
			: m_isbn(isbn), m_title(title), m_author(author), m_crDate(crDate), m_checkedOut(checkout) {}

		string m_isbn, m_title, m_author;
		int m_crDate;
		bool m_checkedOut;
	};

	int getBook(string isbn);
	bool checkedOut(string isbn);
	bool isRegistered(string isbn);
	bool correctISBN(string isbn);

	vector<Book> m_books;
};

// -----------------------------------------------------------------------------

#endif // !_BOOKCLASS_H_
