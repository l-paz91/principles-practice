// -----------------------------------------------------------------------------
#ifndef NUMBERCLASS_H_
#define NUMBERCLASS_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"
#include <type_traits>

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
	template<typename U> Number(const Number<U>& u) { mNumber = u.get(); }

	// ---- operators
	template<typename U> typename common_type<T, U>::type operator+(U u) { return mNumber + u; }
	template<typename U> typename common_type<T, U>::type operator-(U u) { return mNumber - u; }
	template<typename U> typename common_type<T, U>::type operator*(U u) { return mNumber * u; }
	template<typename U> typename common_type<T, U>::type operator/(U u) { return mNumber / u; }
	template<typename U> typename common_type<T, U>::type operator%(U u) { return mNumber % u; }

	template<typename U> typename common_type<T, U>::type operator+(Number<U> i) { return mNumber + i.get(); }
	template<typename U> typename common_type<T, U>::type operator-(Number<U> i) { return mNumber - i.get(); }
	template<typename U> typename common_type<T, U>::type operator*(Number<U> i) { return mNumber * i.get(); }
	template<typename U> typename common_type<T, U>::type operator/(Number<U> i) { return mNumber / i.get(); }
	template<typename U> typename common_type<T, U>::type operator%(Number<U> i) { return mNumber % i.get(); }

	template<typename U> typename common_type<T, U>::type& operator+=(U u) { return mNumber += u; }
	template<typename U> typename common_type<T, U>::type& operator-=(U u) { return mNumber -= u; }
	template<typename U> typename common_type<T, U>::type& operator*=(U u) { return mNumber *= u; }
	template<typename U> typename common_type<T, U>::type& operator/=(U u) { return mNumber /= u; }
	template<typename U> typename common_type<T, U>::type& operator%=(U u) { return mNumber %= u; }

	template<typename U> typename common_type<T, U>::type& operator+=(Number<U> i) { mNumber += i.get(); return *this; }
	template<typename U> typename common_type<T, U>::type& operator-=(Number<U> i) { mNumber -= i.get(); return *this; }
	template<typename U> typename common_type<T, U>::type& operator*=(Number<U> i) { mNumber *= i.get(); return *this; }
	template<typename U> typename common_type<T, U>::type& operator/=(Number<U> i) { mNumber /= i.get(); return *this; }
	template<typename U> typename common_type<T, U>::type& operator%=(Number<U> i) { mNumber %= i.get(); return *this; }

	T& operator=(T t) { return mNumber = t; }
	template<typename U> Number& operator=(Number<U> u) { mNumber = u.get(); return *this; }
						 Number& operator=(Number n)    { mNumber = n.get(); return *this; }

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
	const T& get() const { return mNumber; }

//private:
	T mNumber;
};

// ---- common types (will need to add more if doing different combos)
template<> 
struct common_type < Number<int>, Number<double> >
{
	using type = Number<double>;
};

template<>
struct common_type < Number<double>, Number<char> >
{
	using type = Number<double>;
};

template<>
struct common_type < Number<int>, Number<char> >
{
	using type = Number<int>;
};

template<>
struct common_type < Number<char>, Number<int> >
{
	using type = Number<int>;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !NUMBERCLASS_H_
