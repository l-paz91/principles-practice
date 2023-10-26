// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 14

	Write a function that takes an array of ints as its input and finds the 
	smallest and the largest elements. It should also compute the median and mean. 
	Use a struct holding the results as the return value.

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

struct Results
{
	int mSmallest;
	int mLargest;
	int mMedian;
	int mMean;
};

// -----------------------------------------------------------------------------

struct Results findValues(int* array, int size)
{
	struct Results results;
	results.mSmallest = array[0];
	results.mLargest = array[0];
	results.mMedian = 0;
	results.mMean = 0;

	for (int i = 0; i < size; ++i)
	{
		if (array[i] < results.mSmallest)
		{
			results.mSmallest = array[i];
		}

		if (array[i] > results.mLargest)
		{
			results.mLargest = array[i];
		}

		results.mMean += array[i];
	}

	results.mMedian = array[size / 2];
	results.mMean /= size;

	return results;
}

// -----------------------------------------------------------------------------

int main()
{
	// test findValues()
	int array[20] = { 1, 2, 3, 4, 5, 6, 7, 9, 8, 0, 56, 754, 34, 4321, 9, 333, 666, 91, 100, -10 };
	struct Results results = findValues(array, 20);
	printf("Smallest: %d\nLargest: %d\nMedian: %d\nMean: %d\n", results.mSmallest, results.mLargest, results.mMedian, results.mMean);

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
