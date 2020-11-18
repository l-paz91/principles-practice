// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "Skiplist2.h"

// -----------------------------------------------------------------------------

Skiplist::Skiplist(int pValue)
	: mHead(gMaxLevel, -1)
	, mTail(1, INT_MAX)
	, mLevel(1)
	, mSize(2)
{
	mTail.mNext[0].mNext = nullptr;
	mTail.mNext[0].mValue = -1;
	mHead.mNext[0] = Node(1, pValue);
	mHead.mNext[0].mNext[0] = mTail;

	// make rest of header point at tail for now
	for (int i = 1; i < gMaxLevel; ++i)
		mHead.mNext[i] = mTail;
}

// -----------------------------------------------------------------------------

void Skiplist::print()
{
	Node left = mHead;
	for (int i = mLevel - 1; i >= 0; --i)
	{
		cout << "Level " << i << ": H ";
		while(left.mNext[i].mValue < INT_MAX)
		{
			cout << " --> " << left.mNext[i].mValue;
			left = left.mNext[i];
		}
		left = mHead;
		cout << " --> T" << endl;
	}
}

// -----------------------------------------------------------------------------

void Skiplist::insert(int pValue)
{
	Node* update = new Node[gMaxLevel];
	Node left = mHead;

	for (int i = mLevel-1; i >= 0; --i)
	{
		while (left.mNext[i].mValue < pValue )
		{
			left = left.mNext[i];
		}

		update[i] = left;
	}

	left = left.mNext[0];

	int newLevel = randomLevel();
	if (newLevel > mLevel)
	{
		for (int i = mLevel; i < newLevel; ++i)
		{
			update[i] = mHead;
		}
		mLevel = newLevel;
	}

	left = Node(newLevel, pValue);
	for (int i = 0; i < newLevel; ++i)
	{
		left.mNext[i] = update[i].mNext[i];
		update[i].mNext[i] = left;
	}

	++mSize;
}

// -----------------------------------------------------------------------------

void Skiplist::remove(int pValue)
{
	Node* update = new Node[gMaxLevel];
	Node left = mHead;

	for (int i = mLevel - 1; i >= 0; --i)
	{
		while (left.mNext[i].mValue < pValue)
		{
			left = left.mNext[i];
		}

		update[i] = left;
	}

	left = left.mNext[0];

	if (left.mValue == pValue)
	{
		for (int i = 0; i < mLevel; ++i)
		{
			update[i].mNext[i] = left.mNext[i];		
		}

		delete left.mNext;
		left = mTail;
		while ((mLevel > 1) && (mHead.mNext[mLevel].mValue == INT_MAX))
		{
			mLevel = mLevel - 1;
		}
	}
	--mSize;
}

// -----------------------------------------------------------------------------

Node* Skiplist::findByValue(int pValue)
{
	Node left = mHead;

	for (int i = mLevel - 1; i >= 0; --i)
	{
		while (left.mNext[i].mValue < pValue)
		{
			left = left.mNext[i];
		}
	}

	if (left.mNext)
		return &left.mNext[0];
	else
		return nullptr;
}

// -----------------------------------------------------------------------------

int Skiplist::randomLevel()
{
	int level = 1;

	while ((randint(0, 10) < 5) && (level < log2(mSize)))
		++level;

	return level;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


