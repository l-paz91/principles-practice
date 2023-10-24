// -----------------------------------------------------------------------------
#ifndef InstrusiveList_H
#define InstrusiveList_H
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <memory>

// -----------------------------------------------------------------------------

template<typename T>
class IntrusiveListLink
{
public:
	IntrusiveListLink(const T& pData)
		: mData(pData)
		, mNext(nullptr)
		, mPrev(nullptr)
	{}

	IntrusiveListLink<T>* mNext;
	IntrusiveListLink<T>* mPrev;
	T mData;
};

// -----------------------------------------------------------------------------

template<typename T>
class IntrusiveList
{
public:
	IntrusiveList();
	~IntrusiveList();

	// free all elements in the list
	void clear();

	// add a node to the end of the list
	void pushBack(IntrusiveListLink<T>* pNode);

	// remove a node from the list
	void erase(IntrusiveListLink<T>* pNode);

	// return link at index. "hops" before or after ptr
	IntrusiveListLink<T>* getLinkAt(int index);

	// add a node to the front of the list
	void pushFront(IntrusiveListLink<T>* pNode);

	// insert a node before a given node
	void insert(IntrusiveListLink<T>* pNode, IntrusiveListLink<T>* pNewNode);

	IntrusiveListLink<T>* mFirst;
	IntrusiveListLink<T>* mLast;
};

// -----------------------------------------------------------------------------

template<typename T>
IntrusiveList<T>::~IntrusiveList()
{
	clear();
}

// -----------------------------------------------------------------------------

template<typename T>
void IntrusiveList<T>::clear()
{
	IntrusiveListLink<T>* current = mFirst;
	while (current)
	{
		IntrusiveListLink<T>* next = current->mNext;
		delete current;
		current = next;
	}

	mFirst = nullptr;
	mLast = nullptr;
}

// -----------------------------------------------------------------------------

template<typename T>
IntrusiveList<T>::IntrusiveList()
	: mFirst(nullptr)
	, mLast(nullptr)
{

}

// -----------------------------------------------------------------------------

template<typename T>
void IntrusiveList<T>::pushBack(IntrusiveListLink<T>* pNode)
{
	if (IntrusiveListLink<T>* last = mLast)
	{
		last->mNext = pNode;
		pNode->mPrev = last;
	}
	else
	{
		mFirst = pNode;
		pNode->mPrev = nullptr;
	}

	mLast = pNode;
	pNode->mNext = nullptr;
}

// -----------------------------------------------------------------------------

template<typename T>
void IntrusiveList<T>::erase(IntrusiveListLink<T>* pNode)
{
	if (pNode == mFirst)
	{
		if (pNode->mNext)
		{
			mFirst = pNode->mNext;
			pNode->mNext->mPrev = nullptr;
		}
		else
		{
			mFirst = nullptr;
			mLast = nullptr;
		}
	}
	else if (pNode == mLast)
	{
		if (pNode->mPrev)
		{
			mLast = pNode->mPrev;
			pNode->mPrev->mNext = nullptr;
		}
		else
		{
			mFirst = nullptr;
			mLast = nullptr;
		}
	}
	else
	{
		pNode->mPrev->mNext = pNode->mNext;
		pNode->mNext->mPrev = pNode->mPrev;
	}

	// free the node
	delete pNode;
}

// -----------------------------------------------------------------------------

template<typename T>
IntrusiveListLink<T>* IntrusiveList<T>::getLinkAt(int index)
{
	IntrusiveListLink<T>* current = mFirst;
	for (int i = 0; i < index; ++i)
	{
		current = current->mNext;
	}

	return current;
}

// -----------------------------------------------------------------------------


template<typename T>
void IntrusiveList<T>::pushFront(IntrusiveListLink<T>* pNode)
{
	if (IntrusiveListLink<T>* first = mFirst)
	{
		first->mPrev = pNode;
		pNode->mNext = first;
	}
	else
	{
		mLast = pNode;
		pNode->mNext = nullptr;
	}

	mFirst = pNode;
	pNode->mPrev = nullptr;
}

// -----------------------------------------------------------------------------


template<typename T>
void IntrusiveList<T>::insert(IntrusiveListLink<T>* pNode, IntrusiveListLink<T>* pNewNode)
{
	if (pNode == mFirst)
	{
		pushFront(pNewNode);
	}
	else
	{
		pNode->mPrev->mNext = pNewNode;
		pNewNode->mPrev = pNode->mPrev;
		pNode->mPrev = pNewNode;
		pNewNode->mNext = pNode;
	}
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !InstrusiveList_H
