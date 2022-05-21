// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 23 - Exercise 6

	Write a program that finds dates in a text file. Write out each line containing 
	at least one date in the format line-number: line. Start with a regular expression 
	for a simple format, e.g., 12/24/2000, and test the program with that. Then, 
	add more formats.

	Doesn't test for validation, like 31st February as that isn't really what regex is
	for.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <regex>

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void printMatches(const vector<string>& v, regex& pattern)
{
	int matchesFound = 0;

	for (uint32 i = 0; i < v.size(); ++i)
	{
		smatch matches;
		if (regex_search(v[i], matches, pattern))
		{
			cout << i + 1 << ": " << v[i] << endl;
			++matchesFound;
		}
	}

	cout << "Matches found: " << matchesFound << endl;
}

// -----------------------------------------------------------------------------

void fct()
{
	// get the information
	vector<string> txtFile;

	ifstream in{ "dateExamples.txt" };
	for (string s; getline(in, s);)
	{
		txtFile.push_back(s);
	}

	// first pattern mm/dd/yyyy
	// 2 matches
	regex pat1{ R"(\d\d\/\d\d\/\d{4})" };
	cout << "Pattern mm/dd/yyyy" << endl;
	printMatches(txtFile, pat1);

	// second pattern: 1-4 digits, separator, 1-2 digits, separator, 1-4 digits
	// 12 matches
	regex pat2{ R"(\d{1,4}[/ .-]\d{1,2}[/ .-]\d{1,4})" };
	cout << "\nPattern 1-4 digits, separator, 1-2 digits, separator, 1-4 digits" << endl;
	printMatches(txtFile, pat2);

	// third pattern (ISO format): yyyyMMddTHH:mmzzz
	// 5 matches
	regex pat3{ R"(\d{8}T\d\d:?\d\d[-+]\d{4})" };
	cout << "\nPattern (ISO format): yyyyMMddTHH:mmzzz or yyyyMMddTHHmmzzz" << endl;
	printMatches(txtFile, pat3);

	// fourth pattern: Year Month Day || Day Month Year
	// 6 matches
	regex pat4{ R"(\d{1,4}(rd|st|th)?[ -/.]([jJ]anuary|[fF]ebruary|[mM]arch|[aA]pril|[mM]ay|[jJ]une|[jJ]uly|[aA]ugust|[sS]eptember|[oO]ctober|[nN]ovember|[dDecember])[ -/.]\d{1,4}(rd|st|th)?)" };
	cout << "\nPattern Year Month Day || Day Month Year" << endl;
	printMatches(txtFile, pat4);

	// fifth pattern: Month Day Year || Month Year Day
	// 1 match
	regex pat5{ R"(([jJ]anuary|[fF]ebruary|[mM]arch|[aA]pril|[mM]ay|[jJ]une|[jJ]uly|[aA]ugust|[sS]eptember|[oO]ctober|[nN]ovember|[dDecember])[ -/.]\d{1,4}(rd|st|th)?[ -/.]\d{1,4})" };
	cout << "\nPattern Month Day Year || Month Year Day" << endl;
	printMatches(txtFile, pat5);
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
