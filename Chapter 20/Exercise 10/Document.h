// -----------------------------------------------------------------------------
#ifndef DOCUMENT_H
#define DOCUMENT_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

#include "TextIterator.h"

// -----------------------------------------------------------------------------

// a document is a list of lines
struct Document
{
	Document()
	{
		// every document starts with a single empty line
		// here it makes an empty line and pushes it into the list of lines
		mLine.push_back(Line{});
	}

	// first character of first line
	TextIterator begin()
	{
		return TextIterator(mLine.begin(), (*mLine.begin()).begin());
	}

	TextIterator end()
	{
		auto last = mLine.end();
		--last;		// we know that the document is not empty
		return TextIterator(last, (*last).end());
	}

	list<Line> mLine;
};

// -----------------------------------------------------------------------------

// reading and splitting the lines can be done with this
istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch); )
	{
		d.mLine.back().push_back(ch);	// add the character
		if (ch == '\n')
			d.mLine.push_back(Line{});  // add another line
	}

	if (d.mLine.back().size())
		d.mLine.push_back(Line{});		// add a final empty line

	return is;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif	// !DOCUMENT_H
