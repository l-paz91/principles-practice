// ---------------------------------------------------------------------------//
//BookClass.cpp
// ---------------------------------------------------------------------------//

//to get round using deprecated C code
#define _CRT_SECURE_NO_DEPRECATE

//--INCLUDES--//
#include "BookClass.h"

// -----------------------------------------------------------------------------

Books& Books::getInstance()
{
	static Books Instance;
	return Instance;
}

// -----------------------------------------------------------------------------

Book Books::getBook(string isbn) const
{
	for (int i = 0; i < m_books.size(); ++i)
	{
		if (m_books[i] == isbn)
			return m_books[i];
	}
}

// -----------------------------------------------------------------------------

//add a book to m_books
bool Books::add(string title, string author, string isbn, int crDate, Genre genre)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
		return false;

	//check if copyright date is valid
	if (!validYear(crDate))
		return false;

	//check if book is already registered
	if (isRegistered(isbn))
		return false;

	//allow book to be added
	m_books.push_back(Book(isbn, title, author, crDate, false, genre));

	cout << "Book registered." << endl;

	return true;
}

// -----------------------------------------------------------------------------

//remove a book from m_books
bool Books::remove(string isbn)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
		return false;

	//is the book registered?
	if (!isRegistered(isbn))
		return false;

	//is the book checked out?
	if (checkedOut(isbn))
		return false;

	//allow book to be deleted
	for (uint32_t i = 0; i < m_books.size(); ++i)
	{
		if (m_books[i].m_isbn == isbn)
		{
			m_books.erase(m_books.begin() + i);
			cout << "Book deleted from records." << endl;
			return true;
		}
	}

	cout << "Something weird happened in Books::remove" << endl;
	return false;
}

// -----------------------------------------------------------------------------

bool Books::checkOut(string isbn)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
		return false;

	//is the book registered?
	if (!isRegistered(isbn))
		return false;

	//is the book checked out?
	if (checkedOut(isbn))
		return false;

	//allow book to be checked out
	for (uint32_t i = 0; i < m_books.size(); ++i)
	{
		if (m_books[i].m_isbn == isbn)
		{
			m_books[i].m_checkedOut = true;
			m_booksCheckedOut.push_back(m_books[i]);
			cout << m_books[i].m_title << " successfully checked out." << endl;
			return true;
		}
	}

	cout << "Something weird happened in Books::checkout" << endl;
	return false;
}

// -----------------------------------------------------------------------------

bool Books::checkIn(string isbn)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
		return false;

	//is the book registered?
	if (!isRegistered(isbn))
		return false;

	//is the book checked out?
	if (!checkedOut(isbn))
	{
		cout << "Error: This book has not been checked out." << endl;
		return false;
	}


	//allow book to be checked back in
	for (uint32_t i = 0; i < m_books.size(); ++i)
	{
		if (m_books[i].m_isbn == isbn)
		{
			m_books[i].m_checkedOut = false;
			cout << m_books[i].m_title << " successfully returned." << endl;
			//remove from checked out vector
			for (uint32_t i = 0; i < m_booksCheckedOut.size(); ++i)
			{
				if (m_booksCheckedOut[i].m_isbn == m_books[i].m_isbn)
					m_booksCheckedOut.erase(m_booksCheckedOut.begin() + i);
			}
			return true;
		}
	}

	cout << "Something weird happened in Books::checkIn" << endl;
	return false;
}

// -----------------------------------------------------------------------------

bool Books::checkedOut(string isbn)
{
	for (uint32_t i = 0; i < m_books.size(); ++i)
		if (m_books[i].m_isbn == isbn)
			if (m_books[i].m_checkedOut)
				return true;

	return false;
}

// -----------------------------------------------------------------------------

bool Books::isRegistered(string isbn)
{
	for (uint32_t i = 0; i < m_books.size(); ++i)
		if (m_books[i].m_isbn == isbn)
			return true;

	cout << "That book is not registered." << endl;
	return false;
}

// -----------------------------------------------------------------------------

bool Books::correctISBN(string isbn)
{
	//isbn is the format numbers-numbers-numbers-digitorletter
	//letters can be any number of numbers from x-x-x-9 to xx-xxxx-x-H
	//we can parse this string by checking for '-'

	string temp;
	for (uint32_t i = 0; i < isbn.size(); ++i)
	{
		//look for '-'
		if (isbn[i] != '-')
			temp += isbn[i];
		else
		{
			size_t check;
			check = temp.find_first_not_of("0123456789");
			if (check != string::npos)
			{
				cout << "Not a valid ISBN." << endl;
				return false;
			}

			temp = "";
		}

		//if last digit
		if (i == isbn.size() - 1)
		{
			size_t check;
			check = temp.find_first_not_of("0123456789ABCDEFGHIJKLMNOPQRSTUVWXY");
			if (check != string::npos)
			{
				cout << "Not a valid ISBN." << endl;
				return false;
			}
		}
	}

	//isbn was valid
	return true;
}

// -----------------------------------------------------------------------------

bool Books::validYear(int year)
{
	typedef chrono::system_clock clock;
	//get the current year, taken from https://stackoverflow.com/questions/8343676/how-to-get-current-date-and-time
	//please note, this is deprecated C code, so use it wisely
	time_t currentTime = chrono::system_clock::to_time_t(clock::now());
	struct tm *parts = localtime(&currentTime);	//returns a struct containing year, month and day

	int currentYear = parts->tm_year + 1900;

	if (year > currentYear || year < 1800)
	{
		cout << "Ok future boy, correct year please." << endl;
		return false;
	}

	//year was valid
	return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

bool operator==(const Book & book, string isbn)
{
	if (book.m_isbn == isbn)
		return true;
	else
		return false;
}

// -----------------------------------------------------------------------------

bool operator!=(const Book& book, string isbn)
{
	if (book.m_isbn != isbn)
		return true;
	else
		return false;
}

// -----------------------------------------------------------------------------

ostream & operator<<(ostream & os, const Book& book)
{
	return os << "Title: " << book.m_title << "\n"
			  << "Author: " << book.m_author << "\n"
			  << "Copyright Date: " << book.m_crDate << "\n"
			  << "ISBN: " << book.m_isbn << "\n"
			  << "Genre: " << book.m_genre << "\n"
		      << "Checked Out: " << boolalpha << book.m_checkedOut << endl;
}

// -----------------------------------------------------------------------------

ostream & operator<<(ostream & os, const Genre& genre)
{
	switch (genre)
	{
	case Genre::biography:
		return os << "Biography";
	case Genre::children:
		return os << "Children";
	case Genre::fiction:
		return os << "Fiction";
	case Genre::nonfiction:
		return os << "Non-Fiction";
	case Genre::periodical:
		return os << "Periodical";
	default:
		return os << "Bad genre passed in. How was that even possible?";
	}
}

// -----------------------------------------------------------------------------
