// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 26 - Exercise 4

	Devise a format for test data so that you can define a sequence once and run 
	several tests against it.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TestSequence.h"

// -----------------------------------------------------------------------------

int main()
{
	// sequence --- { testName value { sequence } testResult }
	vector<TestSequenceTypes> sequenceType1 = 
	{
		TestSequenceTypes::eOPEN_BRACE,
		TestSequenceTypes::eTEST_NAME,
		TestSequenceTypes::eVALUE,
		TestSequenceTypes::eOPEN_BRACE,
		TestSequenceTypes::eSEQUENCE,
		TestSequenceTypes::eCLOSE_BRACE,
		TestSequenceTypes::eTEST_RESULT,
		TestSequenceTypes::eCLOSE_BRACE 
	};

	TestSequence<int> testIntSequences;
	testIntSequences.setTestSequenceType(sequenceType1);
	testIntSequences.testType("c26-ex2-testInt.txt");

	TestSequence<float> testFloatSequences;
	testFloatSequences.setTestSequenceType(sequenceType1);
	testFloatSequences.testType("c26-ex2-testFloat.txt");	// should fail on TestFloat1 and TestFloat3

	TestSequence<double> testDoubleSequences;
	testDoubleSequences.setTestSequenceType(sequenceType1);
	testDoubleSequences.testType("c26-ex2-testDouble.txt");

	TestSequence<string> testStringSequences;
	testStringSequences.setTestSequenceType(sequenceType1);
	testStringSequences.testType("c26-ex2-testString.txt");

	// -----------------------------------------------------------------------------

	// sequence --- { testName { sequence } value testResult }
	vector<TestSequenceTypes> sequenceType2 =
	{
		TestSequenceTypes::eOPEN_BRACE,
		TestSequenceTypes::eTEST_NAME,
		TestSequenceTypes::eOPEN_BRACE,
		TestSequenceTypes::eSEQUENCE,
		TestSequenceTypes::eCLOSE_BRACE,
		TestSequenceTypes::eVALUE,
		TestSequenceTypes::eTEST_RESULT,
		TestSequenceTypes::eCLOSE_BRACE
	};

	TestSequence<int> testIntSequences2;
	testIntSequences2.setTestSequenceType(sequenceType2);
	testIntSequences2.testType("c26-ex4-testInt.txt");

	pressKeyToContinue();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
