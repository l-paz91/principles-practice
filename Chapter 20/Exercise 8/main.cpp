// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 8

	Define a function that counts the number of characters in a Document.

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

int numberOfCharsInDocument(const Document& document)
{
	int numOfChars = 0;

	// since we have a list of vectors, just add together the size of the vectors in the document
	for (auto vec = document.mLine.begin(); vec != document.mLine.end(); ++vec)
		numOfChars += static_cast<int>((*vec).size());

	return numOfChars;
}

// -----------------------------------------------------------------------------

void fct()
{
	stringstream ss;
	ss << "A first sentence.\n" << "oh look a second sentence.\n" << "A third sentence.\n"
		<< "There should be 121 characters in total in this document." << endl;

	Document myDocument;
	ss >> myDocument;

	print(myDocument);
	cout << "\nNumber of chars in document: " << numberOfCharsInDocument(myDocument) << endl;
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
