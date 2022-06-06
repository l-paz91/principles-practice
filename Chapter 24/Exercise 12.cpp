// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 12

	Implement
		Matrix<double> operator*(Matrix<double,2>&, Matrix<double>&);
	and
		Matrix<double, N> operator+(Matrix<double, N>&, Matrix<double, N>&)
	If you need to, look up the mathematical definitions in a textbook.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <functional>

#include "Matrix11.h"
#include "MatrixIO11.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

using namespace Numeric_lib;

// -----------------------------------------------------------------------------

Matrix<double> operator*(Matrix<double, 2>& pMatrix2D, Matrix<double>& pMatrix)
{
	const Index n = pMatrix2D.dim1();
	Matrix<double> v(n);

	for (Index i = 0; i < n; ++i)
	{
		v(i) = dot_product(pMatrix2D[i], pMatrix);
	}

	return v;
}

// -----------------------------------------------------------------------------

template<int N>
Matrix<double, N> operator+(Matrix<double, N>& pMatrix1, Matrix<double, N>& pMatrix2)
{
	double* m1Data = pMatrix1.data();
	double* m2Data = pMatrix2.data();

	Matrix<double, N> temp(pMatrix1);
	double* tempArray = temp.data();

	std::transform(m1Data, m1Data+pMatrix1.size(), m2Data, tempArray, std::plus<double>());

	return temp;
}

// -----------------------------------------------------------------------------

double createNum(double& pNumber)
{
	double randNum = randint(1, 2);
	return pNumber = randNum;
}

// -----------------------------------------------------------------------------

void fct()
{
	// initialising a 3d matrix with a 3d array will cause a heap corruption...
	double array3d[2][3][4] = { { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} },
							    { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} } };

	double array2d[5][5] = { { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 } };

	double array[5] = { 1,2,3,4,5 };

	Matrix<double> matrix = array;
	Matrix<double, 2> matrix2d = array2d;
	Matrix<double, 3> matrix3d(2,3,4);
	matrix3d.apply(createNum);

	Matrix<double> mult = matrix2d * matrix;
	Matrix<double, 2> add = matrix2d + matrix2d;
	Matrix<double, 3> add2 = matrix3d + matrix3d;

	cout << "1d matrix: " << matrix << '\n';
	cout << "\n2d Matrix: " << matrix2d << "\n\n";
	cout << "\n3d Matrix: " << matrix3d << "\n\n"; // see MatrixIO11Modified.h

	cout << "\n1d Matrix * 2d Matrix: " <<  mult << '\n';
	cout << "\n2d Matrix + 2d Matrix: \n\n" << add << '\n';
	cout << "\n3d Matrix + 3d Matrix: \n\n" << add2 << '\n';
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
