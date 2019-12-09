// -----------------------------------------------------------------------------
// MoneyClass.cpp
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MoneyClass.h"

// -----------------------------------------------------------------------------

void Money::convertToSmall(double amount)
{
	amount = round(amount*100);		//round using 4/5 rounding rule, found in std library
	m_money = narrow_cast<long int>(amount);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


std::ostream& operator<<(ostream& os, const Money& m)
{
	switch (m.getCurrency())
	{
	case Currency::GBP:
		return os << "GBP" << fixed << setprecision(2) << m.getMoney() << endl;
	case Currency::USD:
		return os << "USD" << fixed << setprecision(2) << m.getMoney() << endl;
	case Currency::DKK:
		return os << "DKK" << fixed << setprecision(2) << m.getMoney() << endl;
	default:
		return os << "something weird happened." << endl;
	}
}

// -----------------------------------------------------------------------------

void operator+(const Money& m1, const Money& m2)
{
	double m1money(m1.getMoney()), m2money(m2.getMoney());

	if (m1.getCurrency() != m2.getCurrency())
		m2money = m2.getMoney() * conversionFactor(m2.getCurrency(), m1.getCurrency());

	Money temp(m1money + m2money, m1.getCurrency());

	cout << m1 << " + " << m2 << " = " << temp << endl;
}

// -----------------------------------------------------------------------------

void operator-(const Money& m1, const Money& m2)
{
	double m1money(m1.getMoney()), m2money(m2.getMoney());

	if (m1.getCurrency() != m2.getCurrency())
		m2money = m2.getMoney() * conversionFactor(m2.getCurrency(), m1.getCurrency());

	Money temp(m1money - m2money, m1.getCurrency());

	cout << m1 << " - " << m2 << " = " << temp << endl;
}

// -----------------------------------------------------------------------------

void operator/(const Money& m1, const Money& m2)
{
	double m1money(m1.getMoney()), m2money(m2.getMoney());

	if (m1.getCurrency() != m2.getCurrency())
		m2money = m2.getMoney() * conversionFactor(m2.getCurrency(), m1.getCurrency());

	Money temp(m1money / m2money, m1.getCurrency());

	cout << m1 << " / " << m2 << " = " << temp << endl;
}

// -----------------------------------------------------------------------------

double conversionFactor(Currency inCurrency, Currency outCurrency)
{
	switch (inCurrency)
	{
	case Currency::GBP:
		if (outCurrency == Currency::USD)
			return 1.32;
		else
			return 8.89;
	case Currency::USD:
		if (outCurrency == Currency::GBP)
			return 0.76;
		else
			return 6.75;
	case Currency::DKK:
		if (outCurrency == Currency::USD)
			return 0.15;
		else
			return 0.11;
	default:
		cout << "Something weird happened" << endl;
		return 0;
	}
}

// -----------------------------------------------------------------------------
