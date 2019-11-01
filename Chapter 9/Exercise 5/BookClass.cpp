// ---------------------------------------------------------------------------//
//BookClass.cpp
// ---------------------------------------------------------------------------//

//--INCLUDES--//
#include "BookClass.h"

// -----------------------------------------------------------------------------

Books& Books::getInstance()
{
	static Books Instance;
	return Instance;
}

// -----------------------------------------------------------------------------

bool Books::add(string title, string author, string isbn, int crDate)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
	{
		cout << "Error: Incorrect ISBN entered." << endl;
		return false;
	}

	//check if book is already registered
	if (isRegistered(isbn))
	{
		cout << "That book has already added." << endl;
		return false;
	}

	//allow book to be added
	m_books.push_back(Book(isbn, title, author, crDate, false));

	return true;
}

// -----------------------------------------------------------------------------

//remove a book from m_books
bool Books::remove(string isbn)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
	{
		cout << "Error: Incorrect ISBN entered." << endl;
		return false;
	}

	//is the book registered?
	if (!isRegistered(isbn))
	{
		cout << "That book is not registered." << endl;
		return false;
	}

	//is the book checked out?
	if (checkedOut(isbn))
	{
		cout << "That book is still checked out and therefore cannot be deleted." << endl;
		return false;
	}

	//allow book to be deleted
	for (int i = 0; i < m_books.size(); ++i)
	{
		if (m_books[i].m_isbn == isbn)
		{
			m_books.erase(m_books.begin() + i);
			cout << "Book deleted from records." << endl;
			return;
		}
	}

	return true;
}

// -----------------------------------------------------------------------------

void Books::checkOut()
{

}

// -----------------------------------------------------------------------------

void Books::checkIn()
{

}

// -----------------------------------------------------------------------------

//returns iterator to book in m_books
int Books::getBook(string isbn)
{
	for (int i = 0; i < m_books.size(); ++i)
		if (m_books[i].m_isbn == isbn)
			return i;
}

// -----------------------------------------------------------------------------

bool Books::checkedOut(string isbn)
{

}

// -----------------------------------------------------------------------------

bool Books::isRegistered(string isbn)
{

}

// -----------------------------------------------------------------------------

bool Books::correctISBN(string isbn)
{

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
