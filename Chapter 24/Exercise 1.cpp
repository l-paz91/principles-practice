// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 1

	The function arguments f for a.apply(f) and apply(f,a) are different. Write a 
	triple() function for each and use each to triple the elements of an array 
	{ 1 2 3 4 5 }. Define a single triple() function that can be used for both 
	a.apply(triple) and apply(triple, a). Explain why it could be a bad idea to 
	write every function to be used by apply() that way.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <type_traits>

#include "Matrix11.h"
#include "MatrixIO11.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

template<typename T>
void triple(T& pNumber)
{
	static_assert(is_arithmetic<T>::value, "Not an arithmetic type.");

	constexpr T t = 3;
	pNumber *= t;
}

// -----------------------------------------------------------------------------

template<typename T>
T triple2(const T& pNumber)
{
	static_assert(is_arithmetic<T>::value, "Not an arithmetic type.");

	constexpr T t = 3;
	return pNumber * t;
}

// -----------------------------------------------------------------------------

template<typename T>
T triple3(T& pNumber)
{
	static_assert(is_arithmetic<T>::value, "Not an arithmetic type.");

	constexpr T t = 3;
	return pNumber *= t;
}

// -----------------------------------------------------------------------------

void fct()
{
	using namespace Numeric_lib;

	int a[] = { 1,2,3,4,5 };

	Matrix<int> m = a;
	Matrix<int> m2(5);

	m.apply(triple3<int>);
	m2 = Numeric_lib::apply(triple3<int>, m);

	cout << m << endl;
	cout << m2 << endl;
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
