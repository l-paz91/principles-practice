// -----------------------------------------------------------------------------
// RationalClass.h
// -----------------------------------------------------------------------------
#ifndef _RATIONALCLASS_H_

//--INCLUDES--//
#include "std_lib_facilities.h"

using namespace std;

// -----------------------------------------------------------------------------

class Rational
{
public:
	//explicit prevents type conversions, so if double is entered, the compiler won't implicitly cast to int "behind the scenes"
	//this will be caught at compile time, so there is no need for error checking
	explicit Rational(int num, int den);
	Rational(const Rational& r) : m_numerator(r.getN()), m_denominator(r.getD()) {}
	~Rational() {}

	void operator=(const Rational& r1) { m_numerator = r1.getN(); m_denominator = r1.getD(); }

	void set(int num, int den);
	int getN() const { return m_numerator; }
	int getD() const { return m_denominator; }
	double rationalToDouble() { return double(m_numerator) / double(m_denominator); }
	void simplify();

private:
	int m_numerator;
	int m_denominator;

};

// -----------------------------------------------------------------------------
// OPERATOR OVERLOADS: CLASS [RATIONAL]
// -----------------------------------------------------------------------------

Rational operator+(Rational& r1, Rational& r2);
Rational operator-(Rational& r1, Rational& r2);
Rational operator*(Rational& r1, Rational& r2);
Rational operator/(Rational& r1, Rational& r2);
ostream& operator<<(ostream& os, const Rational& r);
bool operator==(Rational& r1, Rational& r2);
bool operator!=(Rational& r1, Rational& r2);

// -----------------------------------------------------------------------------

int findGCF(int a, int b);		//find the Greatest Common Factor

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !_RATIONALCLASS_H_

