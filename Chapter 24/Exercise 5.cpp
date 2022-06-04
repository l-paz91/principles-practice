// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 5

	Try the Gaussian elimination program with A == { {0 1} {1 0} } and B == { 5 6 } 
	and watch it fail. Then, try elim_with_partial_pivot().

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

using MatrixD2 = Numeric_lib::Matrix<double, 2>;
using MatrixD1 = Numeric_lib::Matrix<double, 1>;
using In = Numeric_lib::Index;

// -----------------------------------------------------------------------------

MatrixD1 operator*(const MatrixD2& pM, const MatrixD1& pU)
{
	const In n = pM.dim1();
	MatrixD1 v(n);

	for (In i = 0; i < n; ++i)
	{
		v(i) = dot_product(pM[i], pU);
	}

	return v;
}

// -----------------------------------------------------------------------------

void elimWithPartialPivot(MatrixD2& pA, MatrixD1& pB)
{
	const In n = pA.dim1();

	for (In j = 0; j < n; ++j)
	{
		In pivotRow = j;

		// look for a suitable pivot
		for (In k = j+1; k < n; ++k)
		{
			if (abs(pA(k,j)) > abs(pA(pivotRow, j)))
			{
				pivotRow = k;
			}
		}

		// swap the rows if we found a better pivot
		if (pivotRow != j)
		{
			pA.swap_rows(j, pivotRow);
			std::swap(pB(j), pB(pivotRow));
		}

		// elimination
		for (In i = j+1; i < n; ++i)
		{
			const double pivot = pA(j, j);

			if (pivot == 0)
			{
				error("elimWithPartialPivot: Can't solve: pivot == 0");
			}

			const double mult = pA(i, j) / pivot;
			pA[i].slice(j) = scale_and_add(pA[j].slice(j), -mult, pA[i].slice(j));
			pB(i) -= mult * pB(j);
		}
	}
}

// -----------------------------------------------------------------------------

MatrixD1 backSubstitution(const MatrixD2& pA, const MatrixD1& pB)
{
	const In n = pA.dim1();
	MatrixD1 x(n);

	for (In i = n - 1; i >= 0; --i)
	{
		double s = pB(i) - dot_product(pA[i].slice(i + 1), x.slice(i + 1));

		if (double m = pA(i,i))
		{
			x(i) = s / m;
		}
		else
		{
			error("Back Substitution failure.");
		}
	}

	return x;
}

// -----------------------------------------------------------------------------

void classicalElimination(MatrixD2& pA, MatrixD1& pB)
{
	using In = Numeric_lib::Index;
	const In n = pA.dim1();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal
	for (In j = 0; j < n-1; ++j)
	{
		const double pivot = pA(j, j);
		if (pivot == 0)
		{ 
			error("ClassicalElimination: pivot is 0.");
		}

		// fill zeros into each element under the diagonal of the Ith row:
		for (In i = j+1; i < n; ++i)
		{
			const double mult = pA(i, j) / pivot;
			pA[i].slice(j) = scale_and_add(pA[j].slice(j), -mult, pA[i].slice(j));
			pB(i) -= mult * pB(j);	// make the corresponding change to b
		}
	}
}

// -----------------------------------------------------------------------------

MatrixD1 classicalGaussianElimination(MatrixD2 pA, MatrixD1 pB)
{
	//classicalElimination(pA, pB); fails
	elimWithPartialPivot(pA, pB);
	return backSubstitution(pA, pB);
}

// -----------------------------------------------------------------------------

MatrixD1 randomMatrixD1(In pIndex)
{
	MatrixD1 v(pIndex);
	default_random_engine ran((unsigned int)time(0));		// generates integers
	uniform_real_distribution<> ureal{ 0, 1000 };	// maps ints to doubles in [0:INT_MAX)

	for (In i = 0; i < pIndex; ++i)
	{
		v(i) = ureal(ran);
	}

	return v;
}

// -----------------------------------------------------------------------------

MatrixD2 randomMatrixD2(In pIndex)
{
	MatrixD2 v(pIndex, 2);
	default_random_engine ran((unsigned int)time(0));		// generates integers
	uniform_real_distribution<> ureal{ 0, 1000 };

	for (In i = 0; i < v.dim1(); ++i)
	{
		v[i] = ureal(ran);
	}

	return v;
}

// -----------------------------------------------------------------------------

void solveRandomSystem(In pIndex)
{
	double array2d[2][2] = { {0, 1}, {1, 0} };
	double array1d[2] = { 5, 6 };

	MatrixD2 a = array2d;
	MatrixD1 b = array1d;

	//MatrixD2 a = randomMatrixD2(pIndex);	// i think this always has to be an identity matrix, not just random numbers??
	//MatrixD1 b = randomMatrixD1(pIndex);

	cout << "A = " << a << '\n';
	cout << "B = " << b << '\n';

	MatrixD1 x = classicalGaussianElimination(a, b);
	cout << "Classical elim solution is x = " << x << '\n';

	MatrixD1 v = a * x;
	cout << "A * x = " << v << '\n';
}

// -----------------------------------------------------------------------------

void fct()
{
	using namespace Numeric_lib;

	solveRandomSystem(2);
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
