// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 20 - Exercise 2

	Get the Jack-and-Jill example from section 20.1.2 to work. Use input from a 
	couple of small files to test it.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

typedef uint32_t uint32;

// -----------------------------------------------------------------------------

double* getFromJack(int* count)
{
	double* data = new double[10];
	ifstream readIn{ "jackData.txt" };
	if (!readIn)
		error("Error opening jackData.txt");

	for(; *count < 10; ++(*count))
		readIn >> data[*count];

	return data;
}

// -----------------------------------------------------------------------------

vector<double>* getFromJill()
{
	vector<double>* data = new vector<double>(10);
	ifstream readIn{ "jillData.txt" };
	if (!readIn)
		error("Error opening jillData.txt");

	int i = 0;
	while (!readIn.eof())
		readIn >> (*data)[i++];

	return data;
}

// -----------------------------------------------------------------------------

double* high(double* first, double* last)
{
	double h = -1;
	double* high = new double;
	*high = 0;

	for (double* p = first; p != last; ++p)
	{
		if (h < *p)
		{
			high = p;
			h = *p;
		}
	}
	return high;
}

// -----------------------------------------------------------------------------

int main()
{
	int jackCount = 0;
	double* jackData = getFromJack(&jackCount);
	vector<double>& jillData = *getFromJill();

	double* jackHigh = high(jackData, jackData + jackCount);
	double* jillHigh = high(&jillData[0], &jillData[0] + jillData.size());

	cout << "Jill's max: " << *jillHigh << endl;
	cout << "Jack's max: " << *jackHigh << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
