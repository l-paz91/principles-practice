// ---------------------------------------------------------------------------//
//BookClass.h
// ---------------------------------------------------------------------------//
#ifndef _BOOKCLASS_H_

//--INCLUDES--//
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;

// -----------------------------------------------------------------------------

struct Book
{
	Book() {}
	Book(string isbn, string title, string author, int crDate, bool checkout)
		: m_isbn(isbn), m_title(title), m_author(author), m_crDate(crDate), m_checkedOut(checkout) {}

	string m_isbn, m_title, m_author;
	int m_crDate;
	bool m_checkedOut;
};

// -----------------------------------------------------------------------------

class Books
{
public:
	static Books& getInstance();
	~Books() {}								//destructor

	vector<Book> getBooks() const { return m_books; }
	vector<Book> getCBooks() const { return m_booksCheckedOut; }
	Book getBook(string isbn) const;		//return a book

	bool add(string title, string author, string isbn, int crDate);
	bool remove(string isbn);
	bool checkOut(string isbn);
	bool checkIn(string isbn);

private:
	Books() {}								//private constructor to prevent more than one class being created
	Books(const Books&) {}					//private copy constructor to prevent copying by construction
	Books& operator=(const Books&) {}		//private copy constructor to prevent copying by assignment

	bool checkedOut(string isbn);
	bool isRegistered(string isbn);
	bool correctISBN(string isbn);
	bool validYear(int year);

	vector<Book> m_books;
	vector<Book> m_booksCheckedOut;
};

// -----------------------------------------------------------------------------

bool operator==(const Book& book, string isbn);
bool operator!=(const Book& book, string isbn);
ostream& operator<<(ostream& os, const Book& book);

#endif // !_BOOKCLASS_H_

