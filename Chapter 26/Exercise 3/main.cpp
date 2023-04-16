// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 26 - Exercise 3

	Repeat exercise 1 with the version of binary_search that takes a comparison 
	criterion. Make a list of new opportunities for errors introduced by that 
	extra argument.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// my binary search using the bullet points listed at the start at chapter 26
template<typename It, typename T>
bool myBinarySeach(It pBegin, It pEnd, const T& pValue, It& pElement)
{
	if (auto distance = std::distance(pBegin, pEnd))
	{
		It middleElement = pBegin;
		std::advance(middleElement, distance/2);

		// is the middle element equal to what we are searching for?
		if (*middleElement == pValue)
		{
			pElement = middleElement;
			return true;
		}

		// if pValue is less than the middle, we look at left hand half
		if (pValue < *middleElement)
		{
			if (bool leftResult = myBinarySeach(pBegin, middleElement, pValue, pElement))
			{
				pElement = middleElement;
				return leftResult;
			}
		}

		// if pValue is more than middle, we look at right hand half
		if (pValue > *middleElement)
		{
			if (distance > 1)
			{
				if (bool rightResult = myBinarySeach(middleElement, pEnd, pValue, pElement))
				{
					pElement = middleElement;
					return rightResult;
				}
			}
		}
	}

	// we didn't find it
	return false;
}

// -----------------------------------------------------------------------------

template<typename T>
struct Test
{
	vector<T> mSeq;
	string mLabel;
	T mVal;
	bool mRes;

	void reset()
	{
		mSeq.clear();
		mLabel = "";
	}
};

// -----------------------------------------------------------------------------

template<typename T>
istream& operator>>(istream& pInputStream, Test<T>& pTest)
{
	char c;
	pInputStream >> c;

	if (pInputStream.eof())
	{
		return pInputStream;
	}

	if (c != '{')
	{
		error("Test::operator>> test string should open with { ");
		return pInputStream;
	}

	pInputStream >> pTest.mLabel;
	pInputStream >> pTest.mVal;
	pInputStream >> c;

	if (c != '{')
	{
		error("Test::operator>> test string sequence should open with { ");
		return pInputStream;
	}

	string temp;
	while (pInputStream >> temp)
	{
		if (temp == "}")
		{
			pInputStream.unget();
			break;
		}
		T i = from_string<T>(temp);
		pTest.mSeq.push_back(i);
	}
	pInputStream.clear();

	pInputStream >> c;
	if (c != '}')
	{
		error("Test::operator>> test string sequence should end with } ");
		return pInputStream;
	}

	pInputStream >> pTest.mRes;
	pInputStream >> c;

	return pInputStream;
}

// -----------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream& pOutputStream, const Test<T>& pTest)
{
	pOutputStream << "{ " << pTest.mLabel << " " << pTest.mVal << " {";
	for (int i : pTest.mSeq)
		pOutputStream << " " << i;
	pOutputStream << "} " << pTest.mRes << " }";

	return pOutputStream;
}

// -----------------------------------------------------------------------------

template<typename T>
int testAll(istream& pInputStream)
{
	int errorCount = 0;
	for (Test<T> t; pInputStream >> t; t.reset())
	{
		// sort sequence first
		sort(t.mSeq);

		bool result = binary_search(t.mSeq.begin(), t.mSeq.end(), t.mVal);

		if (result != t.mRes)
		{
			cout << "Failure: test " << t.mLabel
				<< "Looking for: " << t.mVal << ", test should be: " << t.mRes
				<< " binary_search: " << t.mSeq.size() << " elements, val == " << t.mVal
				<< " -> " << t.mRes << '\n';
			++errorCount;
		}
	}

	return errorCount;
}

// -----------------------------------------------------------------------------

template<typename T, typename pred>
int testAllWithPredicate(istream& pInputStream, pred pFunc)
{
	int errorCount = 0;
	for (Test<T> t; pInputStream >> t; t.reset())
	{
		// sort sequence first
		sort(t.mSeq);

		bool result = binary_search(t.mSeq.begin(), t.mSeq.end(), t.mVal, pFunc);

		if (result != t.mRes)
		{
			cout << "Failure: test " << t.mLabel
				<< "Looking for: " << t.mVal << ", test should be: " << t.mRes
				<< " binary_search: " << t.mSeq.size() << " elements, val == " << t.mVal
				<< " -> " << t.mRes << '\n';
			++errorCount;
		}
	}

	return errorCount;
}

// -----------------------------------------------------------------------------

template<typename T, typename pred>
void testType(const string& pFilename, pred pFunc)
{
	ifstream inputStream(pFilename);
	int searchResult = testAllWithPredicate<T>(inputStream, pFunc);
	if (searchResult == 0)
	{
		cout << "No errors found.\n";
	}
}

// -----------------------------------------------------------------------------

int main()
{
	// 1 - pass, 2 - fail, 3 - fail
	testType<int>("c26-ex3-testInt.txt", less<int>());

	// 1 - pass, 2 - fail, 3 - pass
	testType<float>("c26-ex3-testFloat.txt", greater<float>());

	// 1 - fail, 2 - fail, 3 - fail
	testType<double>("c26-ex3-testDouble.txt", greater_equal<double>());

	// 1 - fail, 2 - pass, 3 - fail
	testType<string>("c26-ex3-testString.txt", not_equal_to<string>());

	pressKeyToContinue();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
