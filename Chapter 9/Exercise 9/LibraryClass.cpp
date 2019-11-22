// ---------------------------------------------------------------------------//
// LibraryClass.cpp
// ---------------------------------------------------------------------------//

//--INCLUDES--//
#include "LibraryClass.h"

// -----------------------------------------------------------------------------

 Date::Date(int yy, int mm, int dd)
{
	int yearMin(1900), yearMax(3000);
	if (yy > yearMax || yy < yearMin)
		cout << "Invalid year.";
	if (mm > 12 || mm < 1)
		cout << "Invalid month.";
	if (dd > 31 || dd < 1)
		cout << "Invalid day." << endl;
	else
	{
		y = yy; m = mm; d = dd;
	}
}

 // -----------------------------------------------------------------------------

 std::ostream& operator<<(ostream& os, const Date& d)
 {
	 return os << d.d << "/" << d.m << "/" << d.y << endl;
 }

// -----------------------------------------------------------------------------

void Library::checkOutBook(Book& b, Patron& p)
{
	bool bookFound(false), patronFound(false);

	//both book and patron must be in library
	for (int i = 0; i < m_books.size(); ++i)
	{
		if (b == m_books[i])
		{
			bookFound = true;
			break;
		}
	}

	for (int i = 0; i < m_patrons.size(); ++i)
	{
		if (p == m_patrons[i])
		{
			patronFound = true;
			break;
		}
	}

	if (bookFound && patronFound)
	{
		b.setCheckedOut(true);
		Date date(2019, 11, 22);
		m_transactions.push_back(Transaction(p, b, date));
	}
	else
	{
		if (!bookFound)
			cout << "Sorry, that book does not exist." << endl;
		if (!patronFound)
			cout << "Sorry, that user does not exist." << endl;
	}
}

// -----------------------------------------------------------------------------

void Library::modifyBook(Book& book)
{
	for (int i = 0; i < m_books.size(); ++i)
	{
		if (book == m_books[i])
			m_books[i] = book;
	}
}

// -----------------------------------------------------------------------------

void Library::modifyPatron(Patron& patron)
{
	for (int i = 0; i < m_patrons.size(); ++i)
	{
		if (patron == m_patrons[i])
			m_patrons[i] = patron;
	}
}

// -----------------------------------------------------------------------------

vector<std::string> Library::getPatronsWithFees()
{
	vector<string> temp;

	for (int i = 0; i < m_patrons.size(); ++i)
	{
		if (m_patrons[i].owesFees())
			temp.push_back(m_patrons[i].getName());
	}

	return temp;
}

// -----------------------------------------------------------------------------

std::ostream& operator<<(ostream& os, const vector<Transaction>& t)
{
	for (Transaction temp : t)
	{
		os << temp.patron.getName() << " checked out " << temp.book.getTitle() << " on " << temp.date << "\n";
	}

	return os;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
