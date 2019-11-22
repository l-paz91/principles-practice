// ---------------------------------------------------------------------------//
// LibraryClass.h
// ---------------------------------------------------------------------------//
#ifndef _LIBRARY_CLASS_H_

//--INCLUDES--//
#include "PatronClass.h"

// -----------------------------------------------------------------------------

struct Date
{
	Date(int yy, int mm, int dd);

	int y, m, d;
};

ostream& operator<<(ostream& os, const Date& d);

// -----------------------------------------------------------------------------

struct Transaction
{
	Transaction(Patron& p, Book& b, Date& d) : patron(p), book(b), date(d) {}

	Patron patron;
	Book book;
	Date date;
};

// -----------------------------------------------------------------------------

class Library
{
public:
	Library() {}
	~Library() {}

	void addBook(Book& book) { m_books.push_back(book); }
	void addPatron(Patron& patron) { m_patrons.push_back(patron); }
	void checkOutBook(Book& b, Patron& p);

	void modifyBook(Book& book);
	void modifyPatron(Patron& patron);

	vector<string> getPatronsWithFees();
	vector<Transaction> getTransactions() const { return m_transactions; }

private:
	vector<Patron> m_patrons;
	vector<Book> m_books;
	vector<Transaction> m_transactions;
};

ostream& operator<<(ostream& os, const vector<Transaction>& t);

#endif // _LIBRARY_CLASS_H_


