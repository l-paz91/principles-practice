// -----------------------------------------------------------------------------
// MoneyClass.cpp
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MoneyClass.h"

// -----------------------------------------------------------------------------

void Money::convertToSmall(double amount)
{
	round(amount);		//round using 4/5 rounding rule, found in std library
	m_money = narrow_cast<long int>(amount * 100);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


std::ostream& operator<<(ostream& os, const Money& m)
{
	return os << "$" << fixed << setprecision(2) << m.getMoney() << endl;
}

// -----------------------------------------------------------------------------

void operator+(const Money& m1, const Money& m2)
{
	double m1money(m1.getMoney()), m2money(m2.getMoney());

	cout << "$" << m1money << " + " << m2money << " = $" << m1money + m2money << endl;
}

// -----------------------------------------------------------------------------

void operator-(const Money& m1, const Money& m2)
{
	double m1money(m1.getMoney()), m2money(m2.getMoney());

	cout << "$" << m1money << " - " << m2money << " = $" << m1money - m2money << endl;
}

// -----------------------------------------------------------------------------

void operator/(const Money& m1, const Money& m2)
{
	double m1money(m1.getMoney()), m2money(m2.getMoney());

	cout << "$" << m1money << " / " << m2money << " = $" << m1money / m2money << endl;
}

// -----------------------------------------------------------------------------
