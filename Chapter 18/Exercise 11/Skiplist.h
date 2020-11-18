// -----------------------------------------------------------------------------
#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"

const int gMaxLevel = 15; // number of levels allowed in the skiplist (not all these will be used)

// -----------------------------------------------------------------------------

struct Node
{
	Node() {}
	Node(const int pLevel, int pValue)
		: mValue(pValue)
	{
		mNext = new Node[pLevel];
	}
	
	Node* mNext;
	int mValue;	
};

// -----------------------------------------------------------------------------

struct Skiplist
{
	Skiplist(int pValue);
	~Skiplist() { delete[] mHead.mNext; delete[] mTail.mNext; }

	void print();
	void insert(int pValue);	// inserts in numerical order
	void remove(int pValue);	
	Node* findByValue(int pValue);

//private:
	int randomLevel();

	Node mHead;				
	Node mTail;		
	int mLevel;		// number of elements in array that mHead is pointing at
	int mSize;		// number of elements in the skiplist

};


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !_SKIPLIST_H_
