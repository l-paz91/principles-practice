// -----------------------------------------------------------------------------
#ifndef Token_H
#define Token_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Token
{
	Token(char pType) : mName(), mValue(), mType(pType) {}
	Token(double pValue, char pType) : mName(), mValue(pValue), mType(pType) {}
	Token(const string& pName, char pType) : mName(pName), mValue(), mType(pType) {}

	string mName;
	double mValue;
	char mType;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !Token_H
