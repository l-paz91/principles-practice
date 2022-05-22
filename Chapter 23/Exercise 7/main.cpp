// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 23 - Exercise 7

	Write a program (similar to the one in the previous exercise) that finds credit 
	card numbers in a file. Do a bit of research to find out what credit card 
	formats are really used.

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
			cout << i + 1 << ": " << v[i] << "\tMatch: " << matches[0] << endl;
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

	ifstream in{ "testCreditCardNumbers.txt" };
	for (string s; getline(in, s);)
	{
		txtFile.push_back(s);
	}

	// Amex - max length: 15, starts with 34 or 37
	// 3 matches
	regex pat1{ R"((^|\s)3[4|7]\d{13}\s)" };
	cout << "Amex Pattern: " << endl;
	printMatches(txtFile, pat1);

	// Mastercard - max length: 16, starts with 51-55 or 222100-272099
	// 5 matches
	regex pat2{ R"((^|\s)((5[1-5])\d{14}|(((22[2-7]\d{3})|(2[3-7]\d{4}))\d{10}))\s)" };
	cout << "\nMastercard Pattern: " << endl;
	printMatches(txtFile, pat2);

	// Visa - max length: 13-19, starts with 4
	// 6 matches
	regex pat3{ R"((^|\s)4\d{12}[0-9]{0,3}\s)" };
	cout << "\nVisa Pattern: " << endl;
	printMatches(txtFile, pat3);
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
