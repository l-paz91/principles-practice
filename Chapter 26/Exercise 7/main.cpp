// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 26 - Exercise 7

	Test the "simple text editor" from section 20.6.

	Using code from Chapter 20, Exercise 6.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Document.h"

typedef uint32_t uint32;

// -----------------------------------------------------------------------------

void print(Document& d)
{
	cout << "// -----------------------------------------------------------------------------\n";
	int count = 1;


	for (auto it = d.mLine.begin(); it != d.mLine.end(); ++it)
	{
		string line;
		for (char c : *it)
		{
			line += c;
		}

		if (!line.empty())
		{
			cout << "Line " << count++ << " " << line << '\n';
		}
	}


	cout << "\n// -----------------------------------------------------------------------------\n";
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
	line.erase(line.begin() + insertFrom, (line.begin() + insertFrom + stringToReplace.size()));	// erase the word from the vector

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
		if (first == last)
		{
			return last;
		}
		if (*first == firstChar && match(first, last, s))
		{
			return first;
		}
		++first;
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

void testErase()
{
	system("CLS");

	// load some text to put in the document
	const string filename = "DocumentTest.txt";
	ifstream inputStream(filename);

	Document myDocument;
	inputStream >> myDocument;

	cout << "ORIGINAL\n";
	print(myDocument);

	// erase last line
	eraseLine(myDocument, 11);
	cout << "ERASE LAST LINE\n";
	print(myDocument);

	// erase line 1
	eraseLine(myDocument, 0);
	cout << "ERASE FIRST LINE\n";
	print(myDocument);

	// erase single line
	eraseLine(myDocument, 3);
	cout << "ERASE LINE 3\n";
	print(myDocument);

	// erase invalid line
	eraseLine(myDocument, 13);

	// erase a line with an '\n' in it
	eraseLine(myDocument, 6);
	cout << "ERASE LINE WITH NEW LINE CHAR IN IT\n";
	print(myDocument);

	pressKeyToContinue();
}

// -----------------------------------------------------------------------------

bool hasFound(const string& pStringToFind, Document& pDocument)
{
	auto p = find_text(pDocument.begin(), pDocument.end(), pStringToFind);
	if (p == pDocument.end())
	{
		cout << "not found < " << pStringToFind << " > " << endl;
		return false;
	}
	else
	{
		cout << "found the word! < " << pStringToFind << " >" << endl;
		return true;
	}
}

// -----------------------------------------------------------------------------

void testFind()
{
	system("CLS");

	// load some text to put in the document
	const string filename = "DocumentTest.txt";
	ifstream inputStream(filename);

	Document myDocument;
	inputStream >> myDocument;

	cout << "ORIGINAL\n";
	print(myDocument);
	bool result = false;

	// find word not in document
	string wordToFind = "secret";
	result = hasFound(wordToFind, myDocument);

	// find word in document
	wordToFind = "vertical";
	result = hasFound(wordToFind, myDocument);

	// find passed empty string
	wordToFind = "";
	result = hasFound(wordToFind, myDocument);	// should be not found as we don't look for empty strings

	pressKeyToContinue();
}

// -----------------------------------------------------------------------------

void doReplace(const string& pReplacementString, const string& pStringToFind, Document& pDocument)
{
	// this is very inefficient...but it works
	int count = 0;
	while (findAndReplace(pDocument, pStringToFind, pReplacementString))
	{
		++count;
	}
	
	if (!count)
	{
		cout << "\n couldn't find < " << pStringToFind << " > to replace with < " << pReplacementString << " >.\n";
	}
	else
	{
		print(pDocument);
		cout << "\nNo more instances found." << endl;
	}
}

// -----------------------------------------------------------------------------

void testReplace()
{
	system("CLS");

	// load some text to put in the document
	const string filename = "DocumentTest.txt";
	ifstream inputStream(filename);

	Document myDocument;
	inputStream >> myDocument;

	// replace word that exists in document
	doReplace("thou", "you", myDocument);

	// replace word that doesn't exist in document
	doReplace("banana hammock", "watermelon", myDocument);

	// replace word with a newline in it
	doReplace("some\nbody once told me", "\nWithout", myDocument); // shouldn't replace the other without as it's not on newline
}

// -----------------------------------------------------------------------------

int main()
{
	testErase();
	testFind();
	testReplace();

	cout << "\n\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
