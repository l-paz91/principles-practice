// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 10

	How random is your default_random_engine? Write a program that takes two integers 
	n and d as inputs and calls randint(n) d times, recording the result. Output the
	number of draws for each of [0:n] and "eyeball" how similar the counts are. Try 
	with low values for n and with low values for d to see if drawing only a few 
	random numbers causes obvious biases.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void drawRandomNums(int pNumOfDraws, int pMaxRandNum)
{
	system("CLS");

	vector<int> histogram(pMaxRandNum+1);

	for (int i = 0; i < pNumOfDraws; ++i)
	{
		++histogram[int(round(randint(pMaxRandNum)))];
	}

	for (int i = 0; i != histogram.size(); ++i)
	{
		cout << i << '\t';
		for (int j = 0; j != histogram[i]; ++j)
		{
			cout << "*";
		}
		cout << '\n';
	}
}

// -----------------------------------------------------------------------------

void fct()
{
	while (true)
	{
		int numOfDraws = 0;
		int maxRandNum = 0;
		cout << "Num of draws: ";
		cin >> numOfDraws;
		cout << "Max rand num: ";
		cin >> maxRandNum;

		drawRandomNums(numOfDraws, maxRandNum);
	}
}

// -----------------------------------------------------------------------------

int main()
{
	// done to keep an eye on memory tracking (it will always report as a leak if done in main)
	fct();

	cout << "\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
