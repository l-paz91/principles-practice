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

enum class Genre
{
	fiction, nonfiction, periodical, biography, children
};

// -----------------------------------------------------------------------------

struct Book
{
	Book() {}
	Book(string isbn, string title, string author, int crDate, bool checkout, Genre genre)
		: m_isbn(isbn), m_title(title), m_author(author), m_crDate(crDate), m_checkedOut(checkout), m_genre(genre) {}

	string m_isbn, m_title, m_author;
	int m_crDate;
	bool m_checkedOut;
	Genre m_genre;
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

	bool add(string title, string author, string isbn, int crDate, Genre genre);
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
ostream& operator<<(ostream& os, const Genre& genre);	//overkill for a uint_8 but w/e

#endif // !_BOOKCLASS_H_

