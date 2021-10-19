// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 21 - Exercise 14

	Write a program (using the output from the previous exercise) to answer 
	questions such as:
	"How many occurrences of 'ship' are there in a file?"
	"Which word occurs most frequently?"
	"Which is the longest word in the file?"
	"Which is the shortest?"
	"List all words starting with 's'"
	"List all four letter words."

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#include "FileCleanUp.h"

//--GLOBALS--//

// -----------------------------------------------------------------------------

void fct()
{
	// read in file
	FileQuery file("Kacmarcik 2009 paper.txt");

	// due to replacing punctuation with whitespace, some words appear shorter/longer than they are
	cout << "Number of occurrences of 'the': " << file.findNumOfOccurrences("the") << endl;
	cout << "Most frequent word: " << file.findMostOccurring() << endl;
	cout << "Longest word: " << file.findLongestWord() << endl;
	cout << "Shortest word: " << file.findShortestWord() << endl;
	cout << "All words starting with 's': ";  file.listAllWordsStartingWith('s'); cout << endl;
	cout << "All words of size '4': "; file.listAllWordsOfSize(4); cout << endl;
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
