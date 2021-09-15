// -----------------------------------------------------------------------------
#ifndef CHECKEDITERATOR_H
#define CHECKEDITERATOR_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

// adding range checking to std::list iterators
template<typename T>
struct CheckedIterator
{
	using It = typename T::iterator;
	using R = typename std::iterator_traits<It>::reference;	// R for Return type

public:
	CheckedIterator(T* parent)
		: mParent(parent)
		, mCurrent(parent->begin())
	{}

	It& operator++()
	{
		++mCurrent;
		rangeCheck();
		return mCurrent;
	}

	It& operator--()
	{
		--mCurrent;
		rangeCheck();
		return mCurrent;
	}

	It& operator=(const It& it) { mCurrent = it; return mCurrent; }
	R& operator*() { return *mCurrent; }
	const R& operator*() const { return *mCurrent; }

	bool operator==(const It& i) const { return mCurrent == i; }
	bool operator!=(const It& i) const { return mCurrent != i; }

	It& operator+(int n)
	{
		mCurrent = mCurrent + n;
		rangeCheck();
		return mCurrent;
	}

	It& operator+=(CheckedIterator& i)
	{
		auto pos = mCurrent + i.mCurrent;
		mCurrent += pos;
		rangeCheck();
		return mCurrent;
	}

	It& operator+=(int n)
	{
		mCurrent += n;
		rangeCheck();
		return mCurrent;
	}

	It& operator-(int n)
	{
		mCurrent = mCurrent - n;
		rangeCheck();
		return mCurrent;
	}

	It& operator-=(CheckedIterator& i)
	{
		auto pos = mCurrent - i.mCurrent;
		mCurrent -= pos;
		rangeCheck();
		return mCurrent;
	}

	It& operator-=(int n)
	{
		mCurrent -= n;
		rangeCheck();
		return mCurrent;
	}

	void rangeCheck()
	{
		auto start = mParent->begin();
		uint32_t index = 0;
		while (start != mCurrent)
		{
			++index;
			++start;
		}

		if (index >= mParent->size() || index < 0)
			throw Range_error(index);
	}

private:
	T* mParent;
	It mCurrent;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !CHECKEDITERATOR_H
