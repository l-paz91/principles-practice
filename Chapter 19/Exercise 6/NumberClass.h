// -----------------------------------------------------------------------------
#ifndef NUMBERCLASS_H_
#define NUMBERCLASS_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"
#include <type_traits>

// note - char/int operations don't mesh well together. Neither do char/double and char/float
// the opposite way is fine though, so int/char etc.,

// -----------------------------------------------------------------------------

template<typename T>
class Number
{
	// prevent types other than numeric ones being used with this class
	static_assert(is_arithmetic_v<T>, "That's not a numeric type");

public:

	// ---- constructors
	Number() {}
	Number(const T& t) : mNumber(t) {}
	Number(const Number& n) { mNumber = n.get(); }
	template<typename U> Number(const U& u) : mNumber(u) {}

	// ---- operators
	template<typename U> T operator+(U u) { return mNumber += u; }
	template<typename U> T operator-(U u) { return mNumber -= u; }
	template<typename U> T operator*(U u) { return mNumber *= u; }
	template<typename U> T operator/(U u) { return mNumber /= u; }
	template<typename U> T operator%(U u) { return mNumber %= u; }

	template<typename U> Number operator+(Number<U> i) { mNumber += i.get(); return *this; }
	template<typename U> Number operator-(Number<U> i) { mNumber -= i.get(); return *this; }
	template<typename U> Number operator*(Number<U> i) { mNumber *= i.get(); return *this; }
	template<typename U> Number operator/(Number<U> i) { mNumber /= i.get(); return *this; }
	template<typename U> Number operator%(Number<U> i) { mNumber %= i.get(); return *this; }

	template<typename U> T operator+=(U u) { return mNumber += u; }
	template<typename U> T operator-=(U u) { return mNumber -= u; }
	template<typename U> T operator*=(U u) { return mNumber *= u; }
	template<typename U> T operator/=(U u) { return mNumber /= u; }
	template<typename U> T operator%=(U u) { return mNumber %= u; }

	template<typename U> Number operator+=(Number<U> i) { mNumber += i.get(); return *this; }
	template<typename U> Number operator-=(Number<U> i) { mNumber -= i.get(); return *this; }
	template<typename U> Number operator*=(Number<U> i) { mNumber *= i.get(); return *this; }
	template<typename U> Number operator/=(Number<U> i) { mNumber /= i.get(); return *this; }
	template<typename U> Number operator%=(Number<U> i) { mNumber %= i.get(); return *this; }

	T operator=(T t) { return mNumber = t; }
	Number operator=(Number n) { mNumber = n.get(); return *this; }

	friend ostream& operator<<(ostream& os, const Number& n)
	{
		return os << n.mNumber;
	}

	friend istream& operator>>(istream& is, Number& n)
	{
		T i;
		is >> i;
		n.mNumber = i;
		return is;
	}

	// ---- methods
	const T get() const { return mNumber; }

private:
	T mNumber;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !NUMBERCLASS_H_
