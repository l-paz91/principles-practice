// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 8

	Animate the Gaussian elimination.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//

#include <functional> 
#include <type_traits>
#include <Windows.h>

#include "Matrix11.h"
#include "MatrixIO11.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

using MatrixD2 = vector<vector<double>>;
using MatrixD1 = vector<double>;
using In = uint32_t;

// -----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const MatrixD1& v)
{
	os << '{';

	for (In i = 0; i < v.size(); ++i) {
		os << "  ";
		os << v[i];
	}

	os << " }";
	return os;
}

//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const MatrixD2& m)
{
	os << "{\n";

	for (In i = 0; i < m.size(); ++i)
		os << m[i] << '\n';

	os << " }";
	return os;
}

// -----------------------------------------------------------------------------

template <typename T>
void animate(const T& pInMatrix, const string& pComment)
{
	cout << pComment << '\n';
	cout << pInMatrix << '\n';
	cout << "."; Sleep(300); cout << ".";  Sleep(300); cout << ".\n";
}

//-----------------------------------------------------------------------------

MatrixD1 getRow(const MatrixD2& pMatrixD2, In pRowIndex)
{
	MatrixD1 temp;
	for (In i = 0; i < pMatrixD2.size(); ++i)
	{
		temp.push_back(pMatrixD2[pRowIndex][i]);
	}
	return temp;
}

// -----------------------------------------------------------------------------

void modifyRow(MatrixD2& pMatrix1, const MatrixD1& pMatrix2, In pRow)
{
	for (In i = 0; i < pMatrix1.size(); ++i)
	{
		pMatrix1[pRow][i] = pMatrix2[i];
	}
}

// -----------------------------------------------------------------------------

double dotProduct(const MatrixD1& pA, const MatrixD1& pB)
{
	if (pA.size() != pB.size())
		error("sizes wrong for dot product");

	double sum = 0;
	for (In i = 0; i < pA.size(); ++i)
		sum += pA[i] * pB[i];

	return sum;
}

// -----------------------------------------------------------------------------

void swapRows(MatrixD2& pInMatrix, In pRow1, In pRow2)
{
	if (pRow1 == pRow2)
	{
		return;
	}
	In max = pInMatrix.size();
	for (In i = 0; i < max; ++i)
	{
		std::swap(pInMatrix[pRow1][i], pInMatrix[pRow2][i]);
	}
}

// -----------------------------------------------------------------------------

MatrixD1 sliceD1(MatrixD1& pInMatrix, In pIndex)
{
	// this surprisingly works - I'm terrible at shit like this
	// I tried to follow the slice function in Matrix.h
	if (pIndex < 0)
		pIndex = 0;
	else if (pInMatrix.size() < pIndex)
		pIndex = pInMatrix.size();

	MatrixD1 temp(pInMatrix.size(), 0);
	for (In i = pIndex; i < temp.size(); ++i)
	{
		temp[i] = pInMatrix[i];
	}

	return temp;
}

// -----------------------------------------------------------------------------

MatrixD1 scaleAndAdd(const MatrixD1& pMatrix1, const MatrixD1& pMatrix2, double pNum)
{
	if (pMatrix1.size() != pMatrix2.size())
		error("sizes wrong for scale_and_add()");

	MatrixD1 res(pMatrix1.size());
	for (In i = 0; i < pMatrix1.size(); ++i)
	{
		res[i] += pMatrix1[i] * pNum + pMatrix2[i];
	}

	return res;
}

// -----------------------------------------------------------------------------

MatrixD1 operator*(const MatrixD2& pM, const MatrixD1& pU)
{
	const In n = pM.size();
	MatrixD1 v(n);

	for (In i = 0; i < n; ++i)
	{
		v[i] = dotProduct(getRow(pM, i), pU);
	}

	return v;
}

// -----------------------------------------------------------------------------

void elimWithPartialPivot(MatrixD2& pA, MatrixD1& pB)
{
	const In aSize = pA.size();

	for (In j = 0; j < aSize; ++j)
	{
		In pivotRow = j;

		// look for a suitable pivot
		for (In k = j + 1; k < aSize; ++k)
		{
			if (abs(pA[k][j]) > abs(pA[pivotRow][j]))
			{
				pivotRow = k;
			}
		}

		cout << "Suitable pivot point found.\n";

		// swap the rows if we found a better pivot
		if (pivotRow != j)
		{
			swapRows(pA, j, pivotRow);
			std::swap(pB[j], pB[pivotRow]);

			cout << "Better pivot found. Rows swapped.\n";
		}

		// elimination
		for (In i = j + 1; i < aSize; ++i)
		{
			const double pivot = pA[j][j];

			if (pivot == 0)
			{
				error("elimWithPartialPivot: Can't solve: pivot == 0");
			}

			const double mult = pA[i][j] / pivot;

			MatrixD1 rowA = getRow(pA, i);
			MatrixD1 rowB = getRow(pA, j);

			MatrixD1 rowC = sliceD1(rowB, j);
			MatrixD1 rowD = sliceD1(rowA, j);

			modifyRow(pA, scaleAndAdd(rowC, rowD, -mult), i);

			pB[i] -= mult * pB[j];

			animate(pA, "Eliminating: ");
		}

		cout << "Elimination complete\n";
	}
}

// -----------------------------------------------------------------------------

MatrixD1 backSubstitution(const MatrixD2& pA, const MatrixD1& pB)
{
	const In n = pA.size();
	MatrixD1 x(n);

	for (int i = n - 1; i >= 0; --i)
	{
		MatrixD1 rowA = getRow(pA, i);
		double s = pB[i] - dotProduct(sliceD1(rowA, i + 1), sliceD1(x, i + 1));

		if (double m = pA[i][i])
		{
			x[i] = s / m;
		}
		else
		{
			error("Back Substitution failure.");
		}

		animate(x, "Back substitution to new matrix: ");
	}

	cout << "Back substitution complete.\n";
	return x;
}

// -----------------------------------------------------------------------------

void classicalElimination(MatrixD2& pA, MatrixD1& pB)
{
	using In = Numeric_lib::Index;
	const In n = pA.size();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal
	for (In j = 0; j < n - 1; ++j)
	{
		const double pivot = pA[j][j];
		if (pivot == 0)
		{
			error("ClassicalElimination: pivot is 0.");
		}

		// fill zeros into each element under the diagonal of the Ith row:
		for (In i = j + 1; i < n; ++i)
		{
			const double mult = pA[i][j] / pivot;

			MatrixD1 rowA = getRow(pA, j);
			MatrixD1 rowB = getRow(pA, i);

			modifyRow(pA, scaleAndAdd(sliceD1(rowA, j), sliceD1(rowB, j), -mult), i);

			pB[i] -= mult * pB[j];
		}
	}
}

// -----------------------------------------------------------------------------

MatrixD1 classicalGaussianElimination(MatrixD2 pA, MatrixD1 pB)
{
	//classicalElimination(pA, pB);
	elimWithPartialPivot(pA, pB);
	return backSubstitution(pA, pB);
}

// -----------------------------------------------------------------------------

MatrixD1 randomMatrixD1(In pIndex)
{
	MatrixD1 v(pIndex);
	default_random_engine ran((unsigned int)time(0));		// generates integers
	uniform_real_distribution<> ureal{ 0, 10 };	// maps ints to doubles in [0:INT_MAX)

	for (In i = 0; i < pIndex; ++i)
	{
		v[i] = ureal(ran);
	}

	return v;
}

// -----------------------------------------------------------------------------

MatrixD2 randomMatrixD2(In pIndex)
{
	MatrixD2 v(pIndex, MatrixD1(pIndex));
	default_random_engine ran((unsigned int)time(0));		// generates integers
	uniform_real_distribution<> ureal{ 0, 10 };

	for (In row = 0; row < v.size(); ++row)
	{
		for (In col = 0; col < v.size(); ++col)
		{
			v[row][col] = ureal(ran);
		}
	}

	return v;
}

// -----------------------------------------------------------------------------

void solveRandomSystem(In pIndex = 2)
{
	MatrixD2 array2d_1 = { {0, 1}, {1, 0} };
	MatrixD2 array2d_2 = { { 0, 1, 2, 3, 4 },
						   { 1, 1, 3, 4, 8 },
						   { 2, 2, 4, 4, 8 },
						   { 3, 2, 7, 5, 5 },
						   { 5, 4, 3, 4, 7 } };
	MatrixD2 array2d_3 = { {0, 1, 2}, {1, 0, 3}, {2, 8, 7} };

	MatrixD1 array1d_1 = { 5, 6 };
	MatrixD1 array1d_2 = { 9, 8, 1, 5, 6 };
	MatrixD1 array1d_3 = { 5, 6, 7, 8, 9, 10 };

	MatrixD2 a = { {0, 1}, {1, 0} };
	MatrixD1 b = { 5, 6 };

	//MatrixD2 a = randomMatrixD2(pIndex);
	//MatrixD1 b = randomMatrixD1(pIndex);

	cout << "A = " << array2d_2 << '\n';
	cout << "B = " << array1d_2 << '\n';

	MatrixD1 x = classicalGaussianElimination(array2d_2, array1d_2);
	cout << "Classical elim solution is x = " << x << '\n';

	MatrixD1 v = array2d_2 * x;
	cout << "A * x = " << v << '\n';
}

// -----------------------------------------------------------------------------

void fct()
{
	using namespace Numeric_lib;

	solveRandomSystem(5);
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
