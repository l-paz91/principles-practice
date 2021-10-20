// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "FileCleanUp.h"

// -----------------------------------------------------------------------------

void FileQuery::cleanupFile(string pFilename)
{
	map<string, string> contractions
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

	// read in file
	locale loc("en_GB.UTF-8");	// paper has non-ascii chars in it
	ifstream readIn{ pFilename };
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
		auto it = contractions.find(s);
		if (it != contractions.end())
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
		++mWordOccurrence[s];
	}

	string file(ss.str());
	mFile = new string(file);
}

// -----------------------------------------------------------------------------

int FileQuery::findNumOfOccurrences(string pWord)
{
	auto it = mWordOccurrence.find(pWord);
	if (it != mWordOccurrence.end())
	{
		return it->second;
	}
	else
		return 0;
}

// -----------------------------------------------------------------------------

std::string FileQuery::findMostOccurring()
{
	string mostFrequent = mWordOccurrence.begin()->first;
	int n = mWordOccurrence.begin()->second;
	for (auto p : mWordOccurrence)
	{
		if (p.second > n)
		{
			mostFrequent = p.first;
			n = p.second;
		}
	}
	return mostFrequent;
}

// -----------------------------------------------------------------------------

std::string FileQuery::findLongestWord()
{
	string longest = mWordOccurrence.begin()->first;
	for (auto p : mWordOccurrence)
	{
		if (p.first.size() > longest.size())
			longest = p.first;
	}
	return longest;
}

// -----------------------------------------------------------------------------

std::string FileQuery::findShortestWord()
{
	string shortest = mWordOccurrence.begin()->first;
	for (auto p : mWordOccurrence)
	{
		if (p.first.size() < shortest.size())
			shortest = p.first;
	}
	return shortest;
}

// -----------------------------------------------------------------------------

stringstream FileQuery::listAllWordsStartingWith(char c)
{
	stringstream ss;
	for (auto p : mWordOccurrence)
	{
		if (p.first[0] == c ||
			(p.first[0] == ' ' && p.first[1] == c))
			ss << p.first << endl;
	}
	return ss;
}

// -----------------------------------------------------------------------------

stringstream FileQuery::listAllWordsOfSize(int pSize)
{
	stringstream ss;
	for (auto p : mWordOccurrence)
	{
		if (p.first.size() == pSize)
			ss << p.first << endl;
	}
	return ss;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
