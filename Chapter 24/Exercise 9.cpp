// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 9

	Rewrite the non-member apply() functions to return a Matrix of the return type 
	of the function applied; that is, apply(f, a) should return a Matrix<R> where R 
	is the return type of f. Warning: The solution requires information about 
	templates not available in this book.

	Note - I couldn't get all of the triples working...but I managed to get 1 working,
	so there's that.

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
T triple2(const T& pNumber)
{
	static_assert(is_arithmetic<T>::value, "Not an arithmetic type.");

	constexpr T t = 3;
	return pNumber * t;
}

// -----------------------------------------------------------------------------

// fails
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

// cannot be used with functions where pFunction returns void (as you can't create a Matrix of type void...)
// or with a function object...
template<class F, class A>
auto autoApply(F pFunction, A pContainer)
{
	using myType = std::invoke_result_t<F, decltype(pContainer[0])>;

	Numeric_lib::Matrix<myType> copyOfContainer(pContainer.size());
	for (uint32 i = 0; i < pContainer.size(); ++i)
	{
		copyOfContainer[i] = pFunction(pContainer[i]);
	}
	return copyOfContainer;
}

// -----------------------------------------------------------------------------

void fct()
{
	using namespace Numeric_lib;

	int a[] = { 1,2,3,4,5 };

	Matrix<int> m = a;
	Matrix<int> m2(m);

	auto m3 = autoApply(triple2<double>, m);

	cout << "m: " << m << endl;
	cout << "m2: " << m2 << endl;
	cout << "m3: " << m3 << endl;
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
