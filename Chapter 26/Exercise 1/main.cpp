// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 26 - Exercise 1

	Run your binary search algorithm from section 26.1 with the tests presented 
	in section 26.3.2.1.

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

struct Test
{
	vector<int> mSeq;
	string mLabel;
	int mVal;
	bool mRes;

	void clear()
	{
		mSeq.clear();
		mLabel = " ";
		mVal = 0;
		mRes = false;
	}
};

// -----------------------------------------------------------------------------

istream& operator>>(istream& pInputStream, Test& pTest)
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

	int i = 0;
	while (pInputStream >> i)
	{
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

ostream& operator<<(ostream& pOutputStream, const Test& pTest)
{
	pOutputStream << "{ " << pTest.mLabel << " " << pTest.mVal << " {";
	for (int i : pTest.mSeq)
		pOutputStream << " " << i;
	pOutputStream << " } " << pTest.mRes << " }";

	return pOutputStream;
}

// -----------------------------------------------------------------------------

void readInTestsFromFile(const string& pFilename, vector<Test>& pTestVector)
{
	ifstream testFile(pFilename);
	if (testFile.is_open())
	{
		string line;
		//cout << "Original tests from file: \n";
		while (getline(testFile, line))
		{
			//cout << line << '\n';
			istringstream testLineInput(line);
			Test tempTest;
			testLineInput >> tempTest;
			pTestVector.push_back(tempTest);
		}
		testFile.close();
	}
	else
	{
		error("readInTestsFromFile:: Couldn't open file!");
	}
}

// -----------------------------------------------------------------------------

int testAll(istream& pInputStream)
{
	int errorCount = 0;
	for (Test t; pInputStream >> t; t.clear())
	{
		auto iterator = t.mSeq.begin();
		bool result = myBinarySeach(t.mSeq.begin(), t.mSeq.end(), t.mVal, iterator);

		if (result != t.mRes)
		{
			cout << "Failure: test " << t.mLabel
				<< " binary_search: " << t.mSeq.size() << " elements, val == " << t.mVal
				<< " -> " << t.mRes << '\n';
			++errorCount;
		}
	}

	return errorCount;
}

// -----------------------------------------------------------------------------

int main()
{
	const string filename = "TestSequences.txt";
	ifstream inputStream(filename);
	int searchResult = testAll(inputStream);

	pressKeyToContinue();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
