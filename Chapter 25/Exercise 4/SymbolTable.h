// -----------------------------------------------------------------------------
#ifndef SymbolTable_H
#define SymbolTable_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Variable
{
	Variable(string pName, double pValue) : mName(pName), mValue(pValue), mIsConst(false) { }
	Variable(string pName, double pValue, bool pIsConst) : mName(pName), mValue(pValue), mIsConst(pIsConst) { }

	string mName;
	double mValue;
	bool mIsConst;
};

// -----------------------------------------------------------------------------

class SymbolTable
{
public:

	const vector<Variable>& getNames() const { return mNames; }

	void addName(string pName, double pValue, bool pIsConst) { mNames.push_back(Variable(pName, pValue, pIsConst)); }

	double	getValue(string pName);
	void	setValue(string pName, double pValue);
	int		isDeclared(string pName);
	int		isSetConst(string pName);
	void	reassignVariable(string pName, double pValue, bool pIsConst);
	double	defineName(string pName, double pValue, bool pIsConst);

private:
	vector<Variable> mNames;
};

// -----------------------------------------------------------------------------

namespace SymbolKeywords
{
	const string quitKey = "quit";
	const string helpKey = "help";
	const string sqrtKey = "sqrt";
	const string letKey = "let";
	const string powKey = "pow";
	const string constKey = "const";
}

// -----------------------------------------------------------------------------

enum Symbol : const char
{
	let = '#',
	quit = 'Q',
	print = ';',
	number = '8',
	name = 'a',
	sqrtCh = 's',
	powCh = 'p',
	constCh = 'c',
	help = 'H',
	newLine = '\n',
	err = 'e',
	bitwiseAND = '&',
	bitwiseOR = '|',
	bitwiseXOR = '^',
	bitwiseNOT = '~'
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SymbolTable_H
