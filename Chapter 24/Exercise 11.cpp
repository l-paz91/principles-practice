// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 24 - Exercise 11

	Write a swap_columns() to match swap_rows() from section 24.5.3. Obviously, 
	to do that you have to read and understand some of the existing Matrix library 
	code. Don't worry too much about efficiency; it is not possible to get 
	swap_columns() to run as fast as swap_rows().

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Matrix11.h"
#include "MatrixIO11.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

using MatrixD2 = Numeric_lib::Matrix<double, 2>;
using In = Numeric_lib::Index;

// -----------------------------------------------------------------------------

void swapRows(MatrixD2& pInMatrix, In pRow1, In pRow2)
{
	if (pRow1 == pRow2)
	{
		return;
	}

	for (In i = 0; i < pInMatrix.dim2(); ++i)
	{
		std::swap(pInMatrix[pRow1][i], pInMatrix[pRow2][i]);
	}
}

// -----------------------------------------------------------------------------

void swapColumns(MatrixD2& pInMatrix, In pCol1, In pCol2)
{
	if (pCol1 == pCol2)
	{
		return;
	}

	for (In i = 0; i < pInMatrix.dim1(); ++i)
	{
		std::swap(pInMatrix[i][pCol1], pInMatrix[i][pCol2]);
	}
}

// -----------------------------------------------------------------------------

void fct()
{
	double array2d[5][5] = { { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 },
					         { 1, 2, 3, 4, 5 } };

	MatrixD2 matrix = array2d;
	MatrixD2 matrix2 = array2d;

	//matrix.swap_rows(2, 4);
	//swapRows(matrix2, 2, 4);

	matrix.swap_columns(2, 3);	// see Matrix11Modified.h, line 523
	swapColumns(matrix2, 2, 4);

	cout << matrix;
	cout << matrix2;
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
