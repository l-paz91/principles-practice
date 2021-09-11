// -----------------------------------------------------------------------------
#ifndef SLIST_H
#define SLIST_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

#include <iterator>

// -----------------------------------------------------------------------------

template<typename T>
struct SListLink
{
	SListLink() : mNext(0), mValue(T()) {}
	SListLink(SListLink* next, const T& t) : mNext(next), mValue(t) {}
	SListLink(SListLink* link) { SListLink(link->mNext, link->mValue); }

	SListLink<T>* mNext;
	T mValue;
};

// -----------------------------------------------------------------------------

// singly linked list in the style of std::forward_list
template<typename T>
class SList
{
public:
	// ---- constructor
	SList() : mHead(nullptr) {}

	// destructor
	~SList() { clear(); }

	// ---- element access
	T& front() { return mHead->mValue; }										// access the first element

	// ---- iterator access
	class Iterator;
	Iterator begin() { return Iterator(mHead); }								// iterator to the beginning
	Iterator end()   { return Iterator(nullptr); }	 							// iterator to one past end; accessing this results in null

	// ---- capacity
	bool empty() const { return !mHead; }										// checks whether container is empty
	
	int maxSize() 
	{ // returns the maximum possible number of elements
		int count = 0;
		Iterator b = begin();
		while (b != nullptr)
		{
			++count;
			if (b.get()->mNext == nullptr)
				return count;
			++b;
		}
		return count;
	}

	Iterator back()
	{ // get iterator to end element
		int dist = maxSize();
		Iterator it = begin();
		for (int i = 0; i < dist-1; ++i)
			++it;
		return it;
	}

	// ---- modifiers
	void clear()
	{ // clears the contents of the list
		while (mHead != nullptr)
		{
			SListLink<T>* p = mHead;
			mHead = mHead->mNext;
			delete p;
		}
	}

	void insertAfter(Iterator position, const T& value)
	{ // inserts elements after an element
		SListLink<T>* newLink = new SListLink<T>(position.get()->mNext, value);
		position.get()->mNext = newLink;
	}

	void eraseAfter(Iterator position)
	{ // removes the element following position
		SListLink<T>* link = position.get();
		if (SListLink<T>* p = link->mNext)
		{
			if (!(link->mNext->mNext))
				link->mNext = nullptr;
			else
				link->mNext = link->mNext->mNext;

			delete p;
		}
	}
		
	void pushFront(const T& value) 
	{ // insert element at the beginning
		if (mHead)
		{
			SListLink<T>* newLink = new SListLink<T>(mHead, value);
			mHead = newLink;
		}
		else
		{
			mHead = new SListLink<T>(nullptr, value);
		}
	}

	void popFront() 
	{ // erase first element
		SListLink<T>* link = mHead;
		mHead = mHead->mNext;
		delete link;
	}

	void resize(int count)
	{ // resizes the list to contain count elements
		int maxsize = maxSize();
		if (count < maxsize)
			error("loss off data");

		Iterator it = back();

		for (int i = maxsize; i < count; ++i)
		{
			insertAfter(it, T());
			++it;
		}
	}

	void swap(SList& other) 
	{ // exchanges elements of this list with elements of other
		SListLink<T>* link1Start = mHead;
		SListLink<T>* link2Start = other.mHead;
		mHead = link2Start;
		other.mHead = link1Start;
	}

private:
	SListLink<T>* mHead;
};

// -----------------------------------------------------------------------------

template<typename T>
class SList<T>::Iterator
{
public:
	Iterator(SListLink<T>* p)
		: mLink{p}
	{}

	Iterator& operator++() { mLink = mLink->mNext; return *this; }
	T& operator*() { return mLink->mValue; }
	SListLink<T>* get() { return mLink; }

	bool operator==(const Iterator& b) const { return mLink == b.mLink; }
	bool operator!=(const Iterator& b) const { return mLink != b.mLink; }

private:
	SListLink<T>* mLink;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !SLIST_H
