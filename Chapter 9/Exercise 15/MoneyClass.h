// -----------------------------------------------------------------------------
// MoneyClass.h
// -----------------------------------------------------------------------------
#ifndef _MONEYCLASS_H_

//--INCLUDES--//
#include "std_lib_facilities.h"

using namespace std;

// -----------------------------------------------------------------------------

enum class Currency
{
	GBP, USD, DKK
};

// -----------------------------------------------------------------------------

class Money
{
public:
	explicit Money(double amount, Currency currency) : m_currency(currency) { convertToSmall(amount); }
	Money(const Money& m) {}
	~Money() {}

	void set(double amount) { convertToSmall(amount); }
	double getMoney() const { return m_money / 100.f; }
	Currency getCurrency() const { return m_currency; }

private:
	void convertToSmall(double amount);

	//due to the next few questions I'm going to keep this variable vague
	long int m_money;		//== 100 pennies or 345 cents, the part of the currency that denotes 1
	Currency m_currency;
};

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS: CLASS [MONEY]
// -----------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Money& m);

void operator+(const Money& m1, const Money& m2);
void operator-(const Money& m1, const Money& m2);
void operator/(const Money& m1, const Money& m2);

// -----------------------------------------------------------------------------

double conversionFactor(Currency inCurrency, Currency outCurrency);

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


#endif // !_MONEYCLASS_H_

