// -----------------------------------------------------------------------------
// RationalClass.cpp
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "RationalClass.h"

// -----------------------------------------------------------------------------

Rational::Rational(int num, int den)
{
	set(num, den);
}

// -----------------------------------------------------------------------------

void Rational::set(int num, int den)
{
	if (num <= 0)
	{
		cout << "Numerator cannot be less than or equal to 0";
		return;
	}
	else if (den <= 0)
	{
		cout << "Denominator cannot be less than or equal to 0";
		return;
	}

	m_numerator = num;
	m_denominator = den;
}

// -----------------------------------------------------------------------------

void Rational::simplify()
{
	//to simplify a fraction, divide the top and bottom by the highest number 
	//that can divide into both numbers exactly, you can do this by finding the
	//greatest common factor using the Euclid algorithm
	int gcf = findGCF(m_numerator, m_denominator);

	m_numerator /= gcf;
	m_denominator /= gcf;
}

// -----------------------------------------------------------------------------

Rational operator+(Rational& r1, Rational& r2)
{
	//find the common denominator
	int n1 = r1.getN() * r2.getD();
	int n2 = r1.getD() * r2.getN();
	int cd = r1.getD() * r2.getD();

	//now just add numerators together and simplify
	Rational temp(n1 + n2, cd);
	temp.simplify();

	return temp;
}

// -----------------------------------------------------------------------------

Rational operator-(Rational& r1, Rational& r2)
{
	//find the common denominator
	int n1 = r1.getN() * r2.getD();
	int n2 = r1.getD() * r2.getN();
	int cd = r1.getD() * r2.getD();

	Rational temp(n1 - n2, cd);
	temp.simplify();

	return temp;
}

// -----------------------------------------------------------------------------

Rational operator*(Rational& r1, Rational& r2)
{
	int n, d;
	n = r1.getN() * r2.getN();
	d = r1.getD() * r2.getD();
	Rational temp(n, d);

	//simplify fraction
	temp.simplify();

	return temp;
}

// -----------------------------------------------------------------------------

Rational operator/(Rational& r1, Rational& r2)
{
	//2nd fraction needs to be turned upside down
	int n, d;
	n = r1.getN() * r2.getD();
	d = r1.getD() * r2.getN();
	Rational temp(n, d);

	//simplify fraction
	temp.simplify();

	return temp;
}

// -----------------------------------------------------------------------------

std::ostream& operator<<(ostream& os, const Rational& r)
{
	if (r.getD() == 1)
		return os << r.getN() << endl;
	else
		return os << r.getN() << "/" << r.getD() << endl;
}

// -----------------------------------------------------------------------------

bool operator==(Rational& r1, Rational& r2)
{
	return r1.getN() == r2.getN() && 
		   r1.getD() == r2.getD();
}

// -----------------------------------------------------------------------------

bool operator!=(Rational& r1, Rational& r2)
{
	return r1.getN() != r2.getN() &&
		   r1.getD() != r2.getD();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

int findGCF(int a, int b)
{
	//basically if they are the same, they are already the GCF
	//if not, keep dividing b and a until the remainder is equal to a
	if (b == 0)
		return a;
	return findGCF(b, a % b);	//recursive
}

// -----------------------------------------------------------------------------
