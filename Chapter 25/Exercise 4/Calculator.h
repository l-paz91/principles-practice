// -----------------------------------------------------------------------------
#ifndef Calculator_H
#define Calculator_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "TokenStream.h"
#include "SymbolTable.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

class Calculator
{
public:
	void printHelp();
	void calculate();

	double defineName(string pName, double pValue, bool pIsConst);

private:
	double squareRoot();
	double powPow();

	double performNOT();

	double primary();
	double term();
	double expression();
	double declaration();
	double statement();

	void cleanUpMess();

private:
	TokenStream mTokenStream;
	SymbolTable mSymbolTable;

};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Calculator_H
