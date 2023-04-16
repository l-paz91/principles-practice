// -----------------------------------------------------------------------------
#ifndef TestSequence_H
#define TestSequence_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

enum class TestSequenceTypes
{
	eOPEN_BRACE,		// {
	eCLOSE_BRACE,		// }
	eTEST_NAME,			// the name of the test
	eSEQUENCE,			// the sequence of values in which to search for the given value
	eVALUE,				  // the value to search for
	eTEST_RESULT		// the result of the test
};

// -----------------------------------------------------------------------------

template<typename T>
class TestSequence
{
public:
	TestSequence() {}

	// -----------------------------------------------------------------------------

	void setTestSequenceType(const vector<TestSequenceTypes>& pTestSequenceType)
	{
		mTestSequenceType = pTestSequenceType;
	}

	// -----------------------------------------------------------------------------

	void testType(const string& pFilename)
	{
		ifstream inputStream(pFilename);
		int searchResult = testAll(inputStream);
		if (searchResult == 0)
		{
			cout << "No errors found.\n";
		}
	}

	// -----------------------------------------------------------------------------

	const vector<TestSequenceTypes>& getTestSequenceType() const { return mTestSequenceType; }

	// -----------------------------------------------------------------------------

private:

	template<typename T>
	struct Test
	{
		Test(TestSequence* pTestSequence)
			: mTestSequence(pTestSequence)
		{}

		vector<T> mSeq;
		string mLabel;
		T mVal;
		bool mRes;
		TestSequence* mTestSequence;

		friend istream& operator>>(istream& pInputStream, Test<T>& pTest)
		{
			for (TestSequenceTypes sType : pTest.mTestSequence->getTestSequenceType())
			{
				switch (sType)
				{
				case TestSequenceTypes::eOPEN_BRACE: case TestSequenceTypes::eCLOSE_BRACE:
				{
					char temp;
					pInputStream >> temp;
					break;
				}

				case TestSequenceTypes::eTEST_NAME:
					pInputStream >> pTest.mLabel;
					break;
				case TestSequenceTypes::eSEQUENCE:
				{
					string tempSequence;
					while (pInputStream >> tempSequence)
					{
						if (tempSequence == "}")
						{
							pInputStream.unget();
							break;
						}
						T i = from_string<T>(tempSequence);
						pTest.mSeq.push_back(i);
					}
					pInputStream.clear();
					break;
				}
				case TestSequenceTypes::eVALUE:
					pInputStream >> pTest.mVal;
					break;
				case TestSequenceTypes::eTEST_RESULT:
					pInputStream >> pTest.mRes;
					break;
				default:
					error("TestSequence::operator>> undefined TestSequenceType");
					break;
				}
			}

			return pInputStream;
		}

		void reset()
		{
			mSeq.clear();
			mLabel = "";
		}
	};

	// -----------------------------------------------------------------------------

	int testAll(istream& pInputStream)
	{
		int errorCount = 0;
		for (TestSequence::Test<T> t(this); pInputStream >> t; t.reset())
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

	vector<TestSequenceTypes> mTestSequenceType;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !TestSequence_H
