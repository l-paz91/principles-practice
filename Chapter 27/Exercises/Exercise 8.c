// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 8

	What is the lexicographical order on your machine? Write out every character 
	on your keyboard together with its integer value; then, write the characters 
	out in the order determined by their integer value.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

// -----------------------------------------------------------------------------

#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <crtdbg.h>

// -----------------------------------------------------------------------------

void keepWindowOpen()
{
	printf("\nPress any key to continue...");
	_getch();
}

// -----------------------------------------------------------------------------

// this function prints out the keyboard in lexicographical order and shows the 
// order determined by their integer value
void printKeyboard()
{
	for (int i = 0; i < 256; ++i)
	{
		printf("%c = %d\n", i, i);
	}
}

// -----------------------------------------------------------------------------

int main()
{
	printKeyboard();

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
