// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 13

	Write a program that does the equivalent of strings; cin >> s; in C; that is, 
	define an input operation that reads an arbitrarily long sequence of 
	whitespace-terminated characters into a zero-terminated array of chars.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

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

// the basic idea here is to dynamically allocate memory as you read characters,
// resizing the array as needed
char* readString()
{
	int size = 10; // start with a small size and grow as needed
	char* string = (char*)malloc(size * sizeof(char));

	if (!string)
	{
		printf("Error allocating memory!\n");
		return NULL;
	}

	int length = 0; // keep track of the length of the string
	char ch = '\0';

	while (1)
	{
		ch = getchar();

		if (ch == '\n' || ch == '\t')
		{
			string[length] = '\0';
			break;
		}

		if (length + 1 >= size)
		{
			size *= 2;
			string = realloc(string, size);

			if (!string)
			{
				printf("Error reallocating memory!\n");
				return NULL;
			}
		}

		string[length] = ch;
		length++;
	}

	string[length] = '\0';
	return string;
}

// -----------------------------------------------------------------------------

int main()
{
	printf("Enter a string (terminate with enter): ");
	char* string = readString();
	printf("You entered: %s\n", string);

	free(string);

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
