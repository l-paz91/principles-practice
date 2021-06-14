// -----------------------------------------------------------------------------
#ifndef EXERCISE5_H
#define EXERCISE5_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

typedef uint32_t uint32;

// -----------------------------------------------------------------------------

template<typename T>
istream& operator>>(istream& inStream, vector<T>& inVector)
{
	cout << "Enter data: ";

	if (inStream.eof())
	{
		inStream.clear();
		inStream.ignore(INT_MAX, '\n');
	}

	string s;
	while (getline(inStream, s))
	{
		stringstream ss(s);
		T t;
		ss >> t;
		inVector.push_back(t);
	}

	return inStream;
}

// -----------------------------------------------------------------------------

istream& operator>>(istream& inStream, vector<string>& inVector)
{
	cout << "Enter data: ";

	if (inStream.eof())
	{
		inStream.clear();
		inStream.ignore(INT_MAX, '\n');
	}

	string s;
	while (getline(inStream, s))
		inVector.push_back(s);

	return inStream;
}

// -----------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream& outStream, vector<T>& inVector)
{
	outStream << "Vector: ";
	for (const T value : inVector)
		outStream << value << ", ";

	return outStream;
}

// -----------------------------------------------------------------------------

void fct()
{
	// vector of strings
	vector<string> vString;
	cin >> vString;
	cout << vString << endl;

	// vector of doubles
	vector<double> vDouble;
	cin >> vDouble;
	cout << vDouble << endl;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !EXERCISE5_H
