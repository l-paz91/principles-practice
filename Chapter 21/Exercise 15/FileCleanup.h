// -----------------------------------------------------------------------------
#ifndef FILECLEANUP_H
#define FILECLEANUP_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

#include <map>

// -----------------------------------------------------------------------------

struct FileQuery
{
	FileQuery() : mFile(nullptr) {}

	FileQuery(string pFilename)
		: mFile(nullptr)
	{
		cleanupFile(pFilename);
	}

	~FileQuery()
	{
		if (mFile)
			delete mFile;
	}

	void cleanupFile(string pFilename);
	int findNumOfOccurrences(string pWord);
	string findMostOccurring();
	string findLongestWord();
	string findShortestWord();
	stringstream listAllWordsStartingWith(char c);
	stringstream listAllWordsOfSize(int pSize);

	map<string, int> mWordOccurrence;
	string* mFile;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !FILECLEANUP_H
