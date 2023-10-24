// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 6

	Change the representation of Link and List from section 27.9 without changing 
	the user interface provided by the functions. Allocate Links in an array of 
	links and have the members first, last, pre, and suc be ints (indices into the array).

	Note: This code kind of works, but it's very broken. I'm not sure how to fix it.
	Also don't really care, I'm not a fan of this exercise.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#define MAX_LINKS 100
#define INVALID_INDEX -1

// -----------------------------------------------------------------------------

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
	int mFirst;
	int mLast;
};

// -----------------------------------------------------------------------------

// link for doubly-linked list
struct Link
{
	int mPrev;
	int mNext;
};

// -----------------------------------------------------------------------------

struct Name
{
	// the link required by List operations
	struct Link mLink;

	// the name of the string
	char* mString;
};

// -----------------------------------------------------------------------------

// where all links are stored
struct Name allLinks[MAX_LINKS];

// keep track of the next free index in allLinks
int nextFreeIndex = 0;

// -----------------------------------------------------------------------------

struct Name* makeName(char* pName)
{
	assert(nextFreeIndex < MAX_LINKS);

	allLinks[nextFreeIndex].mString = pName;
	allLinks[nextFreeIndex].mLink.mNext = INVALID_INDEX;
	allLinks[nextFreeIndex].mLink.mPrev = INVALID_INDEX;

	return &allLinks[nextFreeIndex];
}

// -----------------------------------------------------------------------------

// initialise list to empty
void init(struct List* pList)
{
	assert(pList);
	pList->mFirst = pList->mLast = INVALID_INDEX;
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
	assert(pList && (nextFreeIndex < MAX_LINKS));
	{
		int newIndex = nextFreeIndex++;

		// copy the Link to the array
		allLinks[newIndex].mLink = *pPtr;

		int last = pList->mLast;
		if (last != INVALID_INDEX)
		{
			allLinks[last].mLink.mNext = newIndex;
			allLinks[newIndex].mLink.mPrev = last;
			pList->mLast = newIndex;
		}
		else
		{
			pList->mFirst = pList->mLast = newIndex;
			allLinks[newIndex].mLink.mPrev = allLinks[newIndex].mLink.mNext = INVALID_INDEX;
		}
	}
}

// -----------------------------------------------------------------------------

// add ptr at front of list
void pushFront(struct List* pList, struct Link* pPtr)
{
	assert(pList && (nextFreeIndex < MAX_LINKS));
	{
		int newIndex = nextFreeIndex++;

		// copy the Link to the array
		allLinks[newIndex].mLink = *pPtr;

		int first = pList->mFirst;
		if (first != INVALID_INDEX)
		{
			allLinks[first].mLink.mPrev = newIndex;
			allLinks[newIndex].mLink.mNext = first;
			pList->mFirst = newIndex;
		}
		else
		{
			pList->mFirst = pList->mLast = newIndex;
			allLinks[newIndex].mLink.mPrev = allLinks[newIndex].mLink.mNext = INVALID_INDEX;
		}
	}
}

// -----------------------------------------------------------------------------

// insert element before ptr in list
void insert(struct List* pList, int pPtrIndex, struct Link* pElement)
{
	assert(pList && (nextFreeIndex < MAX_LINKS) && (pPtrIndex >= 0) && (pPtrIndex < nextFreeIndex));

	int newIndex = nextFreeIndex++;
	allLinks[newIndex].mLink = *pElement;

	if (pPtrIndex == pList->mFirst)
	{
		pushFront(pList, pElement);
		return;
	}
	else
	{
		allLinks[newIndex].mLink.mPrev = allLinks[pPtrIndex].mLink.mPrev;
		allLinks[newIndex].mLink.mNext = pPtrIndex;
		allLinks[allLinks[pPtrIndex].mLink.mPrev].mLink.mNext = newIndex;
		allLinks[pPtrIndex].mLink.mPrev = newIndex;
	}
}

// -----------------------------------------------------------------------------

// remove ptr from list, return pointer to the link after ptr
int erase(struct List* pList, int pPtrIndex)
{
	assert(pList && (pPtrIndex >= 0) && (pPtrIndex < nextFreeIndex));
	if (pList == 0) return 0;
	
	if (pPtrIndex == pList->mFirst)
	{
		pList->mFirst = allLinks[pPtrIndex].mLink.mNext;
		if (pList->mFirst != INVALID_INDEX)
		{
			allLinks[pList->mFirst].mLink.mPrev = INVALID_INDEX;
		}
		else
		{
			pList->mLast = INVALID_INDEX;
		}
	}
	else if (pPtrIndex == pList->mLast)
	{
		pList->mLast = allLinks[pPtrIndex].mLink.mPrev;
		if (pList->mLast != INVALID_INDEX)
		{
			allLinks[pList->mLast].mLink.mNext = INVALID_INDEX;
		}
		else
		{
			pList->mFirst = INVALID_INDEX;
		}
	}
	else
	{
		allLinks[allLinks[pPtrIndex].mLink.mPrev].mLink.mNext = allLinks[pPtrIndex].mLink.mNext;
		allLinks[allLinks[pPtrIndex].mLink.mNext].mLink.mPrev = allLinks[pPtrIndex].mLink.mPrev;
	}

	// clear the link
	memset(&allLinks[pPtrIndex], 0, sizeof(struct Link));

	// reuse the index	
	nextFreeIndex--;

	return allLinks[pPtrIndex].mLink.mNext;
}

// -----------------------------------------------------------------------------

// return link at index, "hops" before or after ptr
int advance(int pPtrIndex, int pIndex)
{
	assert((pPtrIndex >= 0) && (pPtrIndex < nextFreeIndex));
	int newIndex = nextFreeIndex++;

	if (pIndex > 0)
	{
		while(pIndex-- && allLinks[newIndex].mLink.mNext != INVALID_INDEX)
		{
			newIndex = allLinks[newIndex].mLink.mNext;
		}
	}
	else
	{
		while (pIndex++ && allLinks[newIndex].mLink.mPrev != INVALID_INDEX)
		{
			newIndex = allLinks[newIndex].mLink.mPrev;
		}
	}

	return newIndex;
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
	int currentIndex = names.mFirst;

	printf("---- Initial ----\n\n");
	while (currentIndex != INVALID_INDEX)
	{
		++count;
		printf("element %d: %s\n", count, allLinks[currentIndex].mString);
		currentIndex = allLinks[currentIndex].mLink.mNext;
	}

	// ---- test erase - remove the second name (with index 1)
	erase(&names, advance(names.mFirst, 1));

	currentIndex = names.mFirst;
	count = 0;

	printf("\n---- Test 1 Erase ----\n\n");
	while (currentIndex != INVALID_INDEX)
	{
		++count;
		printf("element %d: %s\n", count, allLinks[currentIndex].mString);
		currentIndex = allLinks[currentIndex].mLink.mNext;
	}

	// ---- test pushFront
	pushFront(&names, makeName("John"));
	pushFront(&names, makeName("Jane"));

	currentIndex = names.mFirst;
	count = 0;

	printf("\n---- Test 2 PushFront ----\n\n");
	while (currentIndex != INVALID_INDEX)
	{
		++count;
		printf("element %d: %s\n", count, allLinks[currentIndex].mString);
		currentIndex = allLinks[currentIndex].mLink.mNext;
	}

	// ---- test insert and advance - Mary should be inserted before Norah
	struct Link* advancedIndex = advance(names.mFirst, 2);
	insert(&names, advancedIndex, makeName("Mary"));

	currentIndex = names.mFirst;
	count = 0;

	printf("\n---- Test 3 Insert ----\n\n");
	while (currentIndex != INVALID_INDEX)
	{
		++count;
		printf("element %d: %s\n", count, allLinks[currentIndex].mString);
		currentIndex = allLinks[currentIndex].mLink.mNext;
	}

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
