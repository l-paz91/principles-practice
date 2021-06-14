// -----------------------------------------------------------------------------
#pragma once

//--INCLUDES--//
#include "pch.h"

/*
    This file is for use with the Google Test Suite that you can add to your
    Visual Studio projects. If you'd like to try them out, I wrote a post on how 
    I did it:
    https://lptcp.blogspot.com/2021/06/automated-testing-adding-google-tests.html
*/

#include "Exercise5.h"

// -----------------------------------------------------------------------------
template<typename T>
class Exercise5_Tests
{
public:

	Exercise5_Tests(T input1, T input2, T input3)
		: m1(input1)
		, m2(input2)
		, m3(input3)
	{}

	void TestInput()
	{
		stringstream ss;
		ss << m1 << "\n" << m2 << "\n" << m3 << "\n";
		ss >> mVector;

		EXPECT_EQ(mVector.size(), 3);

		EXPECT_EQ(mVector[0], m1);
		EXPECT_EQ(mVector[1], m2);
		EXPECT_EQ(mVector[2], m3);
	}

	vector<T> mVector;
	T m1, m2, m3;
};

// -----------------------------------------------------------------------------

template<typename T>
class VectorInputTests
	: public testing::Test
{

};

TYPED_TEST_CASE_P(VectorInputTests);

TYPED_TEST_P(VectorInputTests, InputIsCorrect)
{
	Exercise5_Tests<TypeParam> testClass(
		10.99,
		1001,
		99.9);
	testClass.TestInput();
}

REGISTER_TYPED_TEST_CASE_P(VectorInputTests, InputIsCorrect);

using MyTypes = ::testing::Types<int, float, double>;
INSTANTIATE_TYPED_TEST_CASE_P(Exercise5, VectorInputTests, MyTypes);

// -----------------------------------------------------------------------------

TEST(Exercise5Tests, StringVectorHandlesWhitespaceCorrectly)
{
	Exercise5_Tests<string> testClass(
		"My favourite type of dessert is hot brownies with ice-cream.",
		"banana",
		"this is a sentence." );
	testClass.TestInput();
}

TEST(Exercise5Tests, DoubleVectorInputIsCorrect)
{
	Exercise5_Tests<double> testClass(
		10.99,
		1001,
		99.9 );
	testClass.TestInput();
}

TEST(Exercise5Tests, CharVectorInputIsCorrect)
{
	// my char input only half works, you can't send stuff like '\r' or 12 as the
	//stream converts it to a string and then stringstream gets slightly confused
	//when converting back
	Exercise5_Tests<char> testClass(
		'c',
		'a',
		'f');
	testClass.TestInput();
}

// -----------------------------------------------------------------------------
TEST(Exercise5Tests, StringVectorHandlesWhitespaceInInput)
{
	vector<string> vString;
	stringstream ss;

	string s1 = "My favourite type of dessert is hot brownies with ice-cream.";
	string s2 = "banana";
	string s3 = "this is a sentence.";

	// fake reading in data
	ss << s1 << "\n" << s2 << "\n" << s3 << "\n"; // n is to simulate pressing enter

	ss >> vString;

	EXPECT_EQ(vString.size(), 3);

	EXPECT_EQ(vString[0], s1);
	EXPECT_EQ(vString[1], s2);
	EXPECT_EQ(vString[2], s3);
}

// -----------------------------------------------------------------------------

TEST(Exercise5Tests, DoubleVectorHandlesDoubleInput)
{
	vector<double> vDouble;
	stringstream ss;

	double d1 = 99.1;
	double d2 = 101.10;
	double d3 = 15;

	ss << d1 << "\n" << d2 << "\n" << d3 << "\n";
	ss >> vDouble;

	EXPECT_EQ(vDouble.size(), 3);

	EXPECT_EQ(vDouble[0], d1);
	EXPECT_EQ(vDouble[1], d2);
	EXPECT_EQ(vDouble[2], d3);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
