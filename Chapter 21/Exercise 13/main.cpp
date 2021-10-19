// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 13

	Write a program to "clean up" a text file for use in a word query program; 
	that is, replace punctuation with whitespace, put words into lower case, 
	replace "don't" with "do not" (etc.), and remove plurals (e.g., ships becomes 
	ship. Don't be too ambitious . For example, it is hard to determine plurals
	in general, so just remove an 's' if you find both ship and ships. use that 
	program on a real-world text file with at least 5000 words (e.g., a research 
	paper).
  
  Note - this is disgustingly hacky.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#include "std_lib_facilities.h"

#include <map>

//--GLOBALS--//

// -----------------------------------------------------------------------------

map<string, string> gContractions
{
	{ "aren't", "are not" },
	{ "can't", "can not" },
	{ "could've", "could have" },
	{ "couldn't", "could not" },
	{ "didn't", "did not" },
	{ "doesn't", "does not" },
	{ "don't", "do not" },
	{ "hadn't", "had not" },
	{ "hasn't", "has not" },
	{ "here's", "here is" },
	{ "isn't", "is not" },
	{ "it's", "it is" },
	{ "should've", "should have" },
	{ "shouldn't", "should not" },
	{ "there's", "there is" },
	{ "they're", "they are" },
	{ "they've", "they have" },
	{ "wasn't", "was not" },
	{ "we're", "we have" },
};

// -----------------------------------------------------------------------------

void fct()
{
	// read in file
	locale loc("en_GB.UTF-8");	// paper has non-ascii chars in it
	ifstream readIn{ "Kacmarcik 2009 paper.txt" };
	readIn.imbue(loc);

	stringstream ss;
	while (!readIn.eof())
	{
		string s;
		readIn >> s;

		// change to lowercase
		std::transform(s.begin(), s.end(), s.begin(),
			[](unsigned char c) {return tolower(c); });

		// replace contractions
		auto it = gContractions.find(s);
		if (it != gContractions.end())
		{
			s = it->second;
		}

		// replace punctuation with whitespace
		for (char& c : s)
		{
			if (ispunct(c, loc))	// add locale to prevent crashing (as char could be more than 255)
			{
				c = ' ';
			}
		}

		// remove plurals
		if (s[s.size() - 1] == 's')
			s.pop_back();	// remove last character
		else if (s.size() > 2 && s[s.size() - 2] == 's' && s[s.size() - 1] == ' ')
			s.erase(s.end() - 2);

		ss << s << " " << endl;
	}

	string file(ss.str());		// not pretty

	cout << file << endl;
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
