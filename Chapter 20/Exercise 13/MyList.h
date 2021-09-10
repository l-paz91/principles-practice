// -----------------------------------------------------------------------------
#ifndef MYLIST_H
#define MYLIST_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------


template<typename Elem>
struct Link
{
	Link() : mPrev(0), mSucc(0), mValue(Elem()) {}

	Link(Link* prev, Link* succ, const Elem& elem)
		: mPrev(prev)
		, mSucc(succ)
		, mValue(elem)
	{}

	Link(Link<Elem>* link)
	{
		Link(link->mPrev, link->mSucc, link->mValue);
	}

	Link<Elem>* mPrev;		// previous link
	Link<Elem>* mSucc;		// successor (next) link
	Elem mValue;			// the value
};

// -----------------------------------------------------------------------------

template<typename Elem>
class MyList
{
public:
	MyList() : mHead(nullptr) {}	// allow list to be empty

	//clean up memory
	~MyList()
	{
		while (mHead != nullptr)
		{
			Link<Elem>* p = mHead;
			mHead = mHead->mSucc;
			delete p;
		}
	}

	class Iterator;									// member type: iterator

	Iterator begin() { return Iterator(mHead); }	// iterator to first element
	Iterator end()	 { return Iterator(nullptr); }	// iterator to one beyond last element

	Iterator insert(Iterator p, const Elem& v);		// insert v into list after p
	Iterator erase(Iterator p);						// remove p from the list

	void pushBack(const Elem& v);					// insert v at end
	void pushFront(const Elem& v);					// insert v at front
	void popFront();								// remove first element
	void popBack();									// remove last element

	Elem& front() { return mHead->mValue; }			// the first element
	Elem& back() 									// the last element
	{ 
		for (Iterator it = begin(); it != nullptr; ++it)
		{
			if (it.get()->mSucc == nullptr)
				return it.get()->mValue;
		}

		return front();
	}

private:
	Link<Elem>* mHead;
};

// -----------------------------------------------------------------------------

template<typename Elem>
void MyList<Elem>::pushFront(const Elem& v)
{
	if (mHead)
	{	
		// create new link with its mSucc being current first link
		Link<Elem>* newLink = new Link<Elem>(0, mHead, v);

		// make current first links mPrev point at new link
		mHead->mPrev = newLink;

		// now make the start the new link
		mHead = newLink;
	}
	else
	{
		mHead = new Link<Elem>(0, nullptr, v);	
	}
}

// -----------------------------------------------------------------------------

template<typename Elem>
class MyList<Elem>::Iterator
{
public:
	Iterator(Link<Elem>* p)
		: mCurr{ p }
	{}

	Iterator& operator++() { mCurr = mCurr->mSucc; return *this; }	// forward
	Iterator& operator--() { mCurr = mCurr->mPrev; return *this; }	// backward
	Elem& operator*() { return mCurr->mValue; }						// get contents of
	Link<Elem>* get() const { return mCurr; }					// get pointer to current

	bool operator==(const Iterator& b) const { return mCurr == b.mCurr; }
	bool operator!=(const Iterator& b) const { return mCurr != b.mCurr; }

private:
	Link<Elem>* mCurr;		// current link
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !MYLIST_H
