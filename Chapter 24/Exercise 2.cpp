// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 2

	Do exercise 1 again, but with function objects, rather than functions. 
	Hint: Matrix.h contains examples.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <type_traits>

#include "Matrix11.h"
#include "MatrixIO11.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

template<class T>
struct Triple
{
	void operator()(T& pElement)
	{
		constexpr T t = 3;
		pElement *= t;
	}
};

// -----------------------------------------------------------------------------

template<class T>
struct Triple2
{
	T operator()(T& pElement)
	{
		constexpr T t = 3;
		return pElement * t;
	}
};

// -----------------------------------------------------------------------------

template<class T>
struct Triple3
{
	T operator()(T& pElement)
	{
		constexpr T t = 3;
		return pElement *= t;
	}
};

// -----------------------------------------------------------------------------

void fct()
{
	using namespace Numeric_lib;

	int a[] = { 1,2,3,4,5 };

	Matrix<int> m = a;
	Matrix<int> m2(5);

	m.apply(Triple3<int>());
	m2 = Numeric_lib::apply(Triple3<int>(), m);

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
