// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 1

	Implement versions of strlen(), strcmp(), strcpy().

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

// -----------------------------------------------------------------------------

void keepWindowOpen()
{
	printf("\nPress any key to continue...");
	_getch();
}

// -----------------------------------------------------------------------------

// strlen() takes a c-style string as an argument and returns its length
// determined by the null-terminating character. A C-String is as long as the
// num characters between start and terminating null (without including that)

size_t myStrlen(const char* pString)
{
	size_t length = 0;
	while (*pString)
	{
		++length;
		++pString;
	}

	return length;
}

// -----------------------------------------------------------------------------

// strcmp() compares 2 strings and returns an integer <, ==, or > 0 if string1 is
// found to be <, == or > s2

int myStrcmp(const char* pString1, const char* pString2)
{
	// check the first character, if its == continue till we find a non-matching char
	while (*pString1 && (*pString1 == *pString2))
	{
		++pString1;
		++pString2;
	}

	// if they're completely equal, these will be null
	unsigned char* s1 = (unsigned char*)pString1;
	unsigned char* s2 = (unsigned char*)pString2;

	// minus the first ascii character from the second
	return *s1 - *s2;
}

// -----------------------------------------------------------------------------

// strcpy() copies the string pointed to by source to destination, includes
// terminating null

char* myStrcpy(char* pDestination, const char* pSource)
{
	char* originalDestination = pDestination;

	// the post fix ++ is intentional here
	while (*pDestination++ = *pSource++);

	return originalDestination;
}

// -----------------------------------------------------------------------------

int main()
{
	char* hello = "Hello";
	char* world = "World!";
	char* banana = "banana";
	char* anchovies = "anchovies for breakfast";
	
	// strlen 5-6-6-23
	printf("\nHello is %u characters long.", myStrlen(hello));
	printf("\nWorld! is %u characters long.", myStrlen(world));
	printf("\nBanana is %u characters long.", myStrlen(banana));
	printf("\nAnchovies For Breakfast is %u characters long.", myStrlen(anchovies));

	// strcmp <0, <0, 0, >0
	printf("\n\nStrcmp Hello and World! >%d", myStrcmp(hello, world));
	printf("\nStrcmp World! and Banana >%d", myStrcmp(world, banana));
	printf("\nStrcmp Banana and Banana >%d", myStrcmp(banana, banana));
	printf("\nStrcmp Anchovies For Breakfast and hello >%d", myStrcmp(anchovies, hello));

	// strcpy
	char helloCopy[6]; 
	myStrcpy(helloCopy, hello);
	printf("\n\n%s && %s", hello, helloCopy);

	char worldCopy[7];
	myStrcpy(worldCopy, world);
	printf("\n%s && %s", world, worldCopy);

	char bananaCopy[7];
	myStrcpy(bananaCopy, banana);
	printf("\n%s && %s", banana, bananaCopy);

	char mobileNumber[23];
	myStrcpy(mobileNumber, "+55 896523");
	printf("\n%s && %s", "+55 896523", mobileNumber);

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
