// -----------------------------------------------------------------------------
#ifndef INTCLASS_H_
#define INT_CLASS_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

class Int
{
public:

	// ---- constructors
	Int() {}
	Int(const int& i) : mInt(i) {}
	Int(const Int& i) { mInt = i.get(); }

	// ---- operators -- I don't feel like this is the best way to do it
	int operator+(int i) { return mInt += i; }
	int operator-(int i) { return mInt -= i; }
	int operator*(int i) { return mInt *= i; }
	int operator/(int i) { return mInt /= i; }

	Int operator+(Int i) { mInt += i.get(); return *this; }
	Int operator-(Int i) { mInt -= i.get(); return *this; }
	Int operator*(Int i) { mInt *= i.get(); return *this; }
	Int operator/(Int i) { mInt /= i.get(); return *this; }

	int operator+=(int i) { return mInt += i;  }
	int operator-=(int i) { return mInt -= i; }
	int operator*=(int i) { return mInt *= i; }
	int operator/=(int i) { return mInt /= i; }

	Int operator+=(Int i) { mInt += i.get(); return *this; }
	Int operator-=(Int i) { mInt -= i.get(); return *this; }
	Int operator*=(Int i) { mInt *= i.get(); return *this; }
	Int operator/=(Int i) { mInt /= i.get(); return *this; }

	int operator=(int i) { return mInt = i; }
	Int operator=(Int i) { mInt = i.get(); return *this; }

	friend ostream& operator<<(ostream& os, const Int& i);
	friend istream& operator>>(istream& is, Int& i);

	const int get() const { return mInt; }
	
private:
	int mInt;
};

// -----------------------------------------------------------------------------

ostream& operator<<(ostream & os, const Int& i)
{
	return os << i.mInt;
}

// -----------------------------------------------------------------------------

istream& operator>>(istream& is, Int& i)
{
	int n;
	is >> n;
	i.mInt = n;
	return is;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !INTCLASS_H_
