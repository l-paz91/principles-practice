// ---------------------------------------------------------------------------//
//BookClass.cpp
// ---------------------------------------------------------------------------//

//to get round using deprecated C code
#define _CRT_SECURE_NO_DEPRECATE

//--INCLUDES--//
#include "BookClass.h"

// -----------------------------------------------------------------------------

bool Book::createBook(string isbn, string title, string author, int crDate, bool checkedO)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
		return false;

	//check if copyright date is valid
	if (!correctYear(crDate))
		return false;

	//allow book to be created
	m_isbn = isbn;
	m_title = title;
	m_author = author;
	m_crDate = crDate;
	m_checkedOut = checkedO;

	return true;
}

// -----------------------------------------------------------------------------

void Book::setISBN(string& isbn)
{
	//check if ISBN is correct format
	if (!correctISBN(isbn))
		return;

	m_isbn = isbn;
}

// -----------------------------------------------------------------------------

void Book::setCrDate(uint32_t crDate)
{
	//check if copyright date is valid
	if (!correctYear(crDate))
		return;

	m_crDate = crDate;
}

// -----------------------------------------------------------------------------

bool Book::correctISBN(string isbn)
{
	//isbn is the format numbers-numbers-numbers-digitorletter
	//letters can be any number of numbers from x-x-x-9 to xx-xxxx-x-H
	//we can parse this string by checking for '-'

	string temp;
	size_t check;

	for (uint32_t i = 0; i < isbn.size(); ++i)
	{
		//look for '-'
		if (isbn[i] != '-')
			temp += isbn[i];
		else
		{
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

bool Book::correctYear(uint32_t crDate)
{
	typedef chrono::system_clock clock;
	//get the current year, taken from https://stackoverflow.com/questions/8343676/how-to-get-current-date-and-time
	//please note, this is deprecated C code, so use it wisely
	time_t currentTime = chrono::system_clock::to_time_t(clock::now());
	struct tm *parts = localtime(&currentTime);	//returns a struct containing year, month and day

	uint32_t currentYear = parts->tm_year + 1900;

	if (crDate > currentYear || crDate < 1800)
	{
		cout << "The copyright year is not valid." << endl;
		return false;
	}

	//year was valid
	return true;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

bool operator==(const Book& b1, const Book& b2)
{
	return b1.getISBN() == b2.getISBN();
}

// -----------------------------------------------------------------------------

bool operator!=(const Book& b1, const Book& b2)
{
	return b1.getISBN() != b2.getISBN();
}

// -----------------------------------------------------------------------------

std::ostream& operator<<(ostream& os, const Book& b)
{
	return os << "\n-----------------------------------------------------------------------------"
		      << "\nTitle: " << b.getTitle() << "\n"
			  << "Author: " << b.getAuthor() << "\n"
			  << "Copyright Date: " << b.getCrDate() << "\n"
			  << "ISBN: " << b.getISBN() << "\n"
			  << "Checked Out: " << boolalpha << b.isCheckedOut() 
			  << "\n-----------------------------------------------------------------------------"
		      << endl;
}

// -----------------------------------------------------------------------------
