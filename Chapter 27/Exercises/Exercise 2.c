// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 2

	Complete the intrusive List example in section 27.9 and test it using every 
	function.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

// -----------------------------------------------------------------------------

void keepWindowOpen()
{
	printf("\nPress any key to continue...");
	_getch();
}

// -----------------------------------------------------------------------------

struct List
{
	struct Link* mFirst;
	struct Link* mLast;
};

// -----------------------------------------------------------------------------

// link for doubly-linked list
struct Link
{
	struct Link* mPrev;
	struct Link* mNext;
};

// -----------------------------------------------------------------------------

// initialise list to empty
void init(struct List* pList)
{
	assert(pList);
	pList->mFirst = pList->mLast = 0;
}

// -----------------------------------------------------------------------------

// make a new empty list on free store
struct List* create()
{
	struct List* list = (struct List*)malloc(sizeof(struct List));
	init(list);
	return list;
}

// -----------------------------------------------------------------------------

// free all elements of list
void clear(struct List* pList)
{
	assert(pList);
	{
		struct Link* current = pList->mFirst;
		while (current)
		{
			struct Link* next = current->mNext;
			free(current);
			current = next;
		}
		pList->mFirst = pList->mLast = 0;
	}
}

// -----------------------------------------------------------------------------

// free all elements of list, then free list
void destroy(struct List* pList)
{
	assert(pList);
	clear(pList);
	free(pList);
}

// -----------------------------------------------------------------------------

//add ptr at end of list
void pushBack(struct List* pList, struct Link* pPtr)
{
	assert(pList);
	{
		struct Link* last = pList->mLast;
		if (last)
		{
			last->mNext = pPtr;
			pPtr->mPrev = last;
		}
		else
		{
			pList->mFirst = pPtr;
			pPtr->mPrev = 0;
		}

		pList->mLast = pPtr;
		pPtr->mNext = 0;
	}
}

// -----------------------------------------------------------------------------

// add ptr at front of list
void pushFront(struct List* pList, struct Link* pPtr)
{
	assert(pList);
	{
		struct Link* first = pList->mFirst;
		if (first)
		{
			first->mPrev = pPtr;
			pPtr->mNext = first;
		}
		else
		{
			pList->mLast = pPtr;
			pPtr->mNext = 0;
		}

		pList->mFirst = pPtr;
		pPtr->mPrev = 0;
	}
}

// -----------------------------------------------------------------------------

// insert element before ptr in list
void insert(struct List* pList, struct Link* pPtr, struct Link* pElement)
{
	assert(pList);
	if (pPtr == pList->mFirst)
	{
		pushFront(pList, pElement);
	}
	else
	{
		pElement->mPrev = pPtr->mPrev;
		pElement->mNext = pPtr;
		pPtr->mPrev->mNext = pElement;
		pPtr->mPrev = pElement;
	}
}

// -----------------------------------------------------------------------------

// remove ptr from list, return pointer to the link after ptr
struct Link* erase(struct List* pList, struct Link* pPtr)
{
	assert(pList);
	if (pList == 0) return 0;
	
	if (pPtr == pList->mFirst)
	{
		if (pPtr->mNext)
		{
			pList->mFirst = pPtr->mNext;
			pPtr->mNext->mPrev = 0;
			return pPtr->mNext;
		}
		else
		{
			pList->mFirst = pList->mLast = 0;
			return 0;
		}
	}
	else if (pPtr == pList->mLast)
	{
		if (pPtr->mPrev)
		{
			pList->mLast = pPtr->mPrev;
			pPtr->mPrev->mNext = 0;
		}
		else
		{
			pList->mFirst = pList->mLast = 0;
			return 0;
		}
	}
	else
	{
		pPtr->mNext->mPrev = pPtr->mPrev;
		pPtr->mPrev->mNext = pPtr->mNext;
		return pPtr->mNext;
	}
}

// -----------------------------------------------------------------------------

// return link at index, "hops" before or after ptr
struct Link* advance(struct Link* pPtr, int pIndex)
{
	assert(pPtr);
	struct Link* current = pPtr;
	if (pIndex > 0)
	{
		while (pIndex-- && current->mNext)
		{
			current = current->mNext;
		}
	}
	else
	{
		while (++pIndex && current->mPrev)
		{
			current = current->mPrev;

		}
	}

	return current;
}

// -----------------------------------------------------------------------------

struct Name
{
	// the link required by List operations
	struct Link mLink;

	// the name of the string
	char* mString;
};

// -----------------------------------------------------------------------------

struct Name* makeName(char* pName)
{
	struct Name* name = (struct Name*)malloc(sizeof(struct Name));

	if (name)
	{
		name->mString = pName;
	}

	return name;
}

// -----------------------------------------------------------------------------

int main()
{
	// make a list
	struct List names;

	init(&names);

	// make a few Names and add them to the list
	pushBack(&names, (struct Link*)makeName("Norah"));
	pushBack(&names, (struct Link*)makeName("Annemarie"));
	pushBack(&names, (struct Link*)makeName("Kris"));

	// print names
	int count = 0;
	struct Link* current = names.mFirst;

	printf("---- Initial ----\n\n");
	while (current != 0)
	{
		++count;
		printf("element %d: %s\n", count, ((struct Name*)current)->mString);
		current = current->mNext;
	}

	// ---- test erase - remove the second name (with index 1)
	erase(&names, advance(names.mFirst, 1));

	current = names.mFirst;
	count = 0;

	printf("\n---- Test 1 Erase ----\n\n");
	while (current != 0)
	{
		++count;
		printf("element %d: %s\n", count, ((struct Name*)current)->mString);
		current = current->mNext;
	}

	// ---- test pushFront
	pushFront(&names, (struct Link*)makeName("John"));
	pushFront(&names, (struct Link*)makeName("Jane"));

	current = names.mFirst;
	count = 0;

	printf("\n---- Test 2 PushFront ----\n\n");
	while (current != 0)
	{
		++count;
		printf("element %d: %s\n", count, ((struct Name*)current)->mString);
		current = current->mNext;
	}

	// ---- test insert and advance - Mary should be inserted before Norah
	struct Link* advancedIndex = advance(names.mFirst, 2);
	insert(&names, advancedIndex, (struct Link*)makeName("Mary"));

	current = names.mFirst;
	count = 0;

	printf("\n---- Test 3 Insert ----\n\n");
	while (current != 0)
	{
		++count;
		printf("element %d: %s\n", count, ((struct Name*)current)->mString);
		current = current->mNext;
	}

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
