// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 10

	Define a version of the word-counting program where the user can specify the 
	set of whitespace characters.

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

int wordCountWhenSeperatedByWhitespace(TextIterator start, TextIterator end)
{
	int numOfWords = 0;
	char prevChar = *start;	// prevent double spaces from increasing count

	// iterate through every character in the document
	for (auto ch = start; ch != end; ++ch)
	{
		if (isspace(*ch) && !isspace(prevChar))
			++numOfWords;
		prevChar = *ch;
	}

	return numOfWords;
}

// -----------------------------------------------------------------------------

int wordCountWhenConsecutiveAlphabeticCharacters(TextIterator start, TextIterator end)
{
	int numOfWords = 0;
	char prevChar = *start;	//prevent none alpha chars from increasing count

	// iterate through every character in the document
	for (auto ch = start; ch != end; ++ch)
	{
		if (!isalpha(*ch) && isalpha(prevChar))
			++numOfWords;
		prevChar = *ch;
	}

	return numOfWords;
}

// -----------------------------------------------------------------------------

bool isCustomWhitespace(const char c, const string& whitespaceChars)
{
	size_t found = whitespaceChars.find(c);
	if (found != string::npos)
		return true;
	else
		return false;
}

// -----------------------------------------------------------------------------

// exercise 10
int wordCountWithCustomWhitespaceCharacters(TextIterator start, TextIterator end, string customWhitespace)
{
	int numOfWords = 0;
	char prevChar = *start;	//prevent other custom whitespace chars from increasing count

	// iterate through every character in the document
	for (auto ch = start; ch != end; ++ch)
	{
		if (!isCustomWhitespace(*ch, customWhitespace) && isCustomWhitespace(prevChar, customWhitespace))
			++numOfWords;
		prevChar = *ch;
	}

	return numOfWords;
}

// -----------------------------------------------------------------------------

void fct()
{
	stringstream ss;
	ss << "A.1st.sentENce.\n" << "oh.look a 2nd     sentence.\n" << "A.3rd.sentence.\n"
		<< "There should.be 13 words.in-total in this DOCUment." << endl;

	Document myDocument;
	ss >> myDocument;
	print(myDocument);

	int wordCountWhitespaceSeparated = wordCountWhenSeperatedByWhitespace(myDocument.begin(), myDocument.end());
	cout << "Number of words when separated by whitespace only: " << wordCountWhitespaceSeparated << endl;

	// ---------------------------

	stringstream ss2;
	ss2 << "A.1st.sentENce.\n" << "oh.look a 2nd     sentence.\n" << "A.3rd.sentence.\n"
		<< "There should.be 20 words.in-total in this DOCUment." << endl;

	Document myDocument2;
	ss2 >> myDocument2;
	print(myDocument2);

	int wordCountWhenSequenceOfAlphabeticChars = wordCountWhenConsecutiveAlphabeticCharacters(myDocument.begin(), myDocument.end());
	cout << "Number of words when only sequences of alphabetic characters are counted: " << wordCountWhenSequenceOfAlphabeticChars << endl;

	// ---------------------------

	stringstream ss3;
	ss3 << "A.1st.sentENce.\n" << "oh.look a 2nd     sentence.\n" << "A.3rd.sentence.\n"
		<< "There should.be 7 words.in-total in this DOCUment." << endl;

	Document myDocument3;
	ss3 >> myDocument3;
	print(myDocument3);

	int wordCountWhenCustomWhitespaceChars = wordCountWithCustomWhitespaceCharacters(myDocument.begin(), myDocument.end(), "aA1-9");
	cout << "Number of words when using custom whitespace characters: " << wordCountWhenCustomWhitespaceChars << endl;
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
