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

class Book
{
public:
	Book() {}
	~Book() {}

	//no custom constructors because you cannot return out of a constructor, only throw errors and catch them
	bool createBook(string isbn, string title, string author, int crDate, Genre genre, bool checkedO);
	
	//I hate this - you might as well not have private members
	string getISBN() const { return m_isbn; }
	string getTitle() const { return m_title; }
	string getAuthor() const { return m_author; }
	uint32_t getCrDate() const { return m_crDate; }
	Genre getGenre() const { return m_genre; }
	bool isCheckedOut() const { return m_checkedOut; }

	void setISBN(string isbn);
	void setTitle(string title) { m_title = title; }
	void setAuthor(string author) { m_author = author; }
	void setCrDate(uint32_t crDate);
	void setGenre(Genre genre) { m_genre = genre; }
	void setCheckedOut(bool checkedOut) { m_checkedOut = checkedOut; }

private:
	bool correctISBN(string isbn);
	bool correctYear(uint32_t crDate);

	string m_isbn, m_title, m_author;
	uint32_t m_crDate;
	Genre m_genre;
	bool m_checkedOut;
};

// -----------------------------------------------------------------------------

bool operator==(const Book& b1, const Book& b2);
bool operator!=(const Book& b1, const Book& b2);
ostream& operator<<(ostream& os, const Book& b);
ostream& operator<<(ostream& os, const Genre& genre);	//overkill for a uint_8 but w/e

#endif // !_BOOKCLASS_H_
