// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 3

	Expert level only (this cannot be done with the facilities described in this book): 
	Write an apply(f, a) that can take a void(T&), a T(const T&), and their function 
	object equivalents. Hint: Boost::bind.

	A huge thank you to Rare's rendering/engine/template wizard Keith, for helping
  me solve this exercise.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <functional> 
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
	T operator()(const T& pElement)
	{
		constexpr T t = 3;
		return pElement * t;
	}
};

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

namespace Numeric_lib
{
	// called forEachApply as it was inspired by std::for_each
  
	template<class F, class A>
	A forEachApply(F pFunction, A pContainer)
	{
    // if the return type of pFunction is not void
		if constexpr (!std::is_same_v<std::invoke_result_t<F, decltype(pContainer[0])>, void>)
		{
			A copyOfContainer(pContainer);
			for (Index i = 0; i < pContainer.size(); ++i)
			{
				copyOfContainer[i] = pFunction(pContainer[i]);
			}
			return copyOfContainer;
		}
		else
		{
			for (Index i = 0; i < pContainer.size(); ++i)
			{
				pFunction(pContainer[i]);
			}
			return pContainer;
		}
	}
}

// -----------------------------------------------------------------------------

void fct()
{
	using namespace Numeric_lib;

	int a[] = { 1,2,3,4,5 };

	Matrix<int> m = a;
	Matrix<int> m2(5);
	Matrix<int> m3(5);

	cout << "m:  " << m << endl;

	m2 = Numeric_lib::forEachApply(triple2<int>, m);
	m3 = Numeric_lib::forEachApply(triple<int>, m);
	m = Numeric_lib::forEachApply(Triple2<int>(), m);

	cout << "m2: " << m2 << endl;
	cout << "m3: " << m3 << endl;
	cout << "m:  " << m << endl;
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
