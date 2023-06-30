// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 26 - Exercise 6

	Modify the calculator from Chapter 7 minimally to let it take input from a 
	file and produce output to a file (or use your operating systems facilities 
	for redirecting I/O). Then devise a reasonably comprehensive test for it.

	Using code from Chapter 16, Exercise 9.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Calculator.h"

// -----------------------------------------------------------------------------

int testAll(istream& pInputStream)
{
	int errorCount = 0;
	for (string s; getline(pInputStream, s); )
	{
		string testResult;
		getline(pInputStream, testResult);

		string calcResult = Calculator::calculate(s);

		double expectedResult = from_string<double>(testResult);
		double givenResult = from_string<double>(calcResult);

		if (expectedResult != givenResult)
		{
			cout << "Failure Test:  " << s << " = " << testResult;
			cout << "\nResult given: " << calcResult << '\n';
			++errorCount;
		}
	}

	return errorCount;
}

// -----------------------------------------------------------------------------

int main()
{
	const string filename = "calculatorTests.txt";
	ifstream inputStream(filename);
	int searchResult = testAll(inputStream);

	// should show a failure on sqrt(pow(5, 3))=
	// 8.660254037844386
	// the correct answer is 11.180339999999999

	cout << "\n\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
