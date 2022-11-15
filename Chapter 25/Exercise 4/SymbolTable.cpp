// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "SymbolTable.h"

// -----------------------------------------------------------------------------

double SymbolTable::getValue(string pName)
{
	for (uint32_t i = 0; i < mNames.size(); ++i)
	{
		if (mNames[i].mName == pName)
		{
			return mNames[i].mValue;
		}
	}

	error(pName, " is undefined.");
	return 0;
}

// -----------------------------------------------------------------------------

void SymbolTable::setValue(string pName, double pValue)
{
	for (uint32_t i = 0; i < mNames.size(); ++i)
	{
		if (mNames[i].mName == pName)
		{
			mNames[i].mValue = pValue;
			return;
		}
	}

	error(pName, " is undefined.");
}

// -----------------------------------------------------------------------------

int SymbolTable::isDeclared(string pName)
{
	for (uint32_t i = 0; i < mNames.size(); ++i)
	{	
		if (mNames[i].mName == pName)
		{	
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

int SymbolTable::isSetConst(string pName)
{
	for (uint32_t i = 0; i < mNames.size(); ++i)
	{
		if (mNames[i].mName == pName)
		{
			if (mNames[i].mIsConst == true)
			{	
				return true;
			}
		}
	}

	return false;
}

// -----------------------------------------------------------------------------

void SymbolTable::reassignVariable(string pName, double pValue, bool pIsConst)
{
	for (uint32_t i = 0; i < mNames.size(); ++i)
	{
		if (mNames[i].mName == pName)
		{
			mNames[i].mValue = pValue;
			mNames[i].mIsConst = pIsConst;
		}
	}

	cout << "\nValue re-assigned." << endl;
}

// -----------------------------------------------------------------------------

double SymbolTable::defineName(string pName, double pValue, bool pIsConst)
{
	if (isDeclared(pName))
	{
		if (!isSetConst(pName))
		{	
			reassignVariable(pName, pValue, pIsConst);
		}
		else
		{	
			cout << "\nValue cannot be re-assigned." << endl;
		}
	}
	else
	{
		mNames.push_back(Variable{ pName, pValue, pIsConst });
	}

	return pValue;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
