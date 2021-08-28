// -----------------------------------------------------------------------------
#ifndef TEXTITERATOR_H
#define TEXTITERATOR_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// a line is a vector of characters
using Line = vector<char>;

// -----------------------------------------------------------------------------

// keep track of line and character position within a line
class TextIterator
{
public:
	//start the iterator at line lineIt's character position charPos
	TextIterator(list<Line>::iterator lineIt, Line::iterator charPos)
		: mLine(lineIt)
		, mPos(charPos)
	{}

	char& operator*() { return *mPos; }
	vector<char>::iterator& getPos() { return mPos; }
	list<Line>::iterator& getLineIt() { return mLine; }
	vector<char>& getLine() { return *mLine; }
	TextIterator& operator++();

	bool operator==(const TextIterator& other) const
	{
		return mLine == other.mLine && mPos == other.mPos;
	}

	bool operator!=(const TextIterator& other) const
	{
		return !(*this == other);
	}

private:
	list<Line>::iterator mLine;
	Line::iterator mPos;
};

// -----------------------------------------------------------------------------

TextIterator& TextIterator::operator++()
{
	++mPos;							// proceed to next character
	if (mPos == (*mLine).end())
	{
		++mLine;					// proceed to next line
		mPos = (*mLine).begin();	// bad if line==line.end(); so make sure it isn't
	}
	return *this;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TEXTITERATOR_H

