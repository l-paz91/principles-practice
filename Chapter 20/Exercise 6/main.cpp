// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 6

	Write a find-and-replace operation for Documents based on section 20.6.2

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Document.h"

//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

typedef uint32_t uint32;

//--GLOBALS--//

// -----------------------------------------------------------------------------

void print(Document& d)
{
	cout << "// -----------------------------------------------------------------------------" << endl;
	for (auto line : d)
		cout << line;
	cout << "// -----------------------------------------------------------------------------" << endl;
}

// -----------------------------------------------------------------------------

void eraseLine(Document& d, int lineNum)
{
	if (lineNum < 0 || d.mLine.size() - 1 <= lineNum)
		return;

	auto p = d.mLine.begin();
	advance(p, lineNum);
	d.mLine.erase(p);
}

// -----------------------------------------------------------------------------

bool match(TextIterator p, TextIterator last, const string& s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (*p != s[i])
			return false;
		++p;
	}

	return true;
}

// -----------------------------------------------------------------------------

void replaceText(Document& d, TextIterator startPos, const string& stringToReplace, const string& replacementString)
{
	// get the start line
	auto& line = startPos.getLine();

	// get the index of the start position in the vector
	auto insertFrom = startPos.getPos() - line.begin();

	// see if there are newlines in the search string
	size_t newLineFound = stringToReplace.find('\n');
	while (newLineFound != string::npos)
	{
		//get the next line
		++startPos.getLineIt();
		startPos.getPos() = (*startPos.getLineIt()).begin();
		auto& line2 = startPos.getLine();

		// merge the lines
		line.insert(
			line.end(),
			std::make_move_iterator(line2.begin()),
			std::make_move_iterator(line2.end())
		);

		// delete that line from the document
		d.mLine.erase(startPos.getLineIt());

		// check for more new lines
		newLineFound = stringToReplace.find('\n', newLineFound + 1);
	}

	// now erase entire search string from merged vector
	line.erase(line.begin()+insertFrom, (line.begin() + insertFrom + stringToReplace.size()));	// erase the word from the vector

	// now insert new characters into that line vector
	for (int i = 0; i < replacementString.size(); ++i)
	{
		line.insert(line.begin() + insertFrom, replacementString[i]);
		++insertFrom;
	}
}

// -----------------------------------------------------------------------------

TextIterator find_text(TextIterator first, TextIterator last, const string& s)
{
	if (s.size() == 0)
		return last;		// can't find an empty string

	char firstChar = s[0];
	while (true)
	{
		auto p = find(first, last, firstChar);
		if (p == last || match(p, last, s))
			return p;
		first = ++p;
	}
}

// -----------------------------------------------------------------------------

bool findAndReplace(Document& document, const string& stringToReplace, const string& replacementString)
{
	// does that word exist in the document?
	TextIterator startPos = find_text(document.begin(), document.end(), stringToReplace);
	if (startPos == document.end())
	{
		cout << "End of document." << endl;
		return false;
	}
	else
	{
		cout << "replacing " << stringToReplace << " with " << replacementString << endl;
		replaceText(document, startPos, stringToReplace, replacementString);
		return true;
	}
}

// -----------------------------------------------------------------------------

void fct()
{
	Document myDocument;
	cin >> myDocument;	// will need to enter ctrl+z to stop

	//print(myDocument);
	//eraseLine(myDocument, 1);
	//print(myDocument);

	string wordToFind = "secret";
	string replacementWord = "banana\napple";
	auto p = find_text(myDocument.begin(), myDocument.end(), wordToFind);
	if (p == myDocument.end())
		cout << "not found" << endl;
	else
	{
		cout << "found the word! < " << wordToFind << " >" << endl;
	}

	// this is very inefficient...but it works
	while (findAndReplace(myDocument, wordToFind, replacementWord));
	print(myDocument);
	cout << "\nNo more instances found." << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	keep_window_open();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
