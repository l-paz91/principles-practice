// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 23 - Exercise 8

	Modify the program from section 23.8.7 so that it takes as inputs a pattern 
	and a file name. Its output should be the numbered lines (line-number: line) 
	that contain a match of the pattern. If no matches are found, no output should 
	be produced.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <regex>

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void fct()
{
	// accept a pattern and a set of lines from input
	// check the pattern and search for lines with that pattern
	regex pattern;

	string input;
	cout << "Enter pattern: ";
	getline(cin, input);

	try
	{
		pattern = input;
		cout << "\nPattern: " << input << "\n";
	}
	catch (regex_error e)
	{
		cout << input << " is not a valid regular expression\n";
		pressKeyToContinue();
		exit(1);
	}

	cout << "\nFile name: ";	// using CorporateGibberish.txt
	string file;
	cin >> file;
	ifstream txtFile{file};

	int lineNum = 0;

	for (string line; getline(txtFile, line);)
	{
		++lineNum;
		smatch matches;

		if (regex_search(line, matches, pattern))
		{
			cout << "Line " << lineNum << ": " << line << "\n";
			for (uint32 i = 0; i < matches.size(); ++i)
			{
				cout << "\tMatches[" << i << "]: " << matches[i] << '\n';
			}
		}
	}
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	cout << "\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
