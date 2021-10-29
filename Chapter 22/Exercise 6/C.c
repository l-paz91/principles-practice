// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 22 - Exercise 6

	For each language mentioned in this chapter, look at a popular textbook and 
	see what is used as the first complete program. Write that program in all of 
	the other languages. Warning: This could easily be a 100-program project.

	The exercise I chose is Chapter 3 - Exercise 2:
	"Write a program in C++ that converts from miles to kilometres"

	C
	Built and written using Visual Studio Code on Windows 10 (with the MSVC compiler)
	*Note - Please see my github for the build task if you're interested

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <stdio.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------

bool checkQuit()
{
    printf("Quit? y / n\n>> ");
	char ans;
	ans = getchar();
    if(ans == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}

// -----------------------------------------------------------------------------

int main()
{
	const double m2k = 1.60934;

	printf("This program converts miles to kilometers.");

	bool quit = false;
	double miles = 0.0;

	while (!quit)
	{
		printf("\nMiles To Convert: ");
		scanf("%lf", &miles);
		getchar(); 		// to consume newline created by scanf
        printf("\n>> %lf km\n", miles * m2k);
		quit = checkQuit();
	}

	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
