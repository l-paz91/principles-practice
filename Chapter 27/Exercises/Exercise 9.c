// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 9

	Using only C facilities, including the C standard library, read a sequence of 
	words from stdin and write them to stdout in lexicographical order. Hint: The 
	C sort function is called qsort(); look it up somewhere. Alternatively, insert 
	the words into an ordered list as you read them. There is no C standard library 
	list.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 100

// -----------------------------------------------------------------------------

#include <assert.h>
#include <conio.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------

void keepWindowOpen()
{
	printf("\nPress any key to continue...");
	_getch();
}

// -----------------------------------------------------------------------------

// comparator function for qsort
int compare(const void* pStringA, const void* pStringB)
{
	return strcmp((const char*)pStringA, (const char*)pStringB);
}

// -----------------------------------------------------------------------------

int main()
{
	char words[MAX_WORDS][MAX_WORD_LENGTH];
	int count = 0;

	printf("Enter at least 50 words: \n");

	// I couldn't get the EOF to work so I'm relying on the max words
	while (count < MAX_WORDS && scanf("%99s", words[count]) != EOF)
	{
		count++;
	}

	qsort(words, count, MAX_WORD_LENGTH, compare);

	printf("\nSorted words:\n");
	for (int i = 0; i < count; i++)
	{
		printf("%s\n", words[i]);
	}

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
