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
	FileQuery(string pFilename)
		: mFile(cleanupFile(pFilename))
	{}

	~FileQuery() 
	{ 
		if(mFile)
			delete mFile; 
	}

	string* cleanupFile(string pFilename);
	int findNumOfOccurrences(string pWord);
	string findMostOccurring();
	string findLongestWord();
	string findShortestWord();
	void listAllWordsStartingWith(char c);
	void listAllWordsOfSize(int pSize);

	map<string, int> mWordOccurrence;
	string* mFile;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !FILECLEANUP_H
