// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 12

	Implement a (C-Style string, int) lookup table with operations such as 
	find(struct table*, const char*), insert(struct table*, const char*, int) 
	and remove(struct table*, const char*). The representation of the table could 
	be and array of a struct pair or pair of arrays (const char*[] and int*); you 
	choose. Also choose return types for your functions. Document your design 
	decisions.

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#define _CRT_SECURE_NO_WARNINGS

#define TABLE_SIZE 100
#define NOT_FOUND -1

// -----------------------------------------------------------------------------

#include <assert.h>
#include <conio.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------

void keepWindowOpen()
{
	printf("\nPress any key to continue...");
	_getch();
}

// -----------------------------------------------------------------------------

typedef struct Pair
{
	const char* mKey;
	int mValue;
} Pair;

// -----------------------------------------------------------------------------

typedef struct Table
{
	Pair mItems[TABLE_SIZE];
} Table;

// -----------------------------------------------------------------------------

// initialise the table
void initTable(Table* pTable)
{
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		pTable->mItems[i].mKey = NULL;
		pTable->mItems[i].mValue = NOT_FOUND;
	}
}

// -----------------------------------------------------------------------------

// simple hash function based on string's first character
int hash(const char* pKey)
{
	// multiply by a prime number to better distribute the keys
	unsigned int hash = 0;

	while (*pKey)
	{
		hash = (hash * 31) + *pKey++;
	}

	return hash % TABLE_SIZE;
}

// -----------------------------------------------------------------------------

int find(Table* pTable, const char* pKey)
{
	// this find is quite simple and tries to handle collisions by linear probing
	int index = hash(pKey);
	int originalIndex = index;

	while (pTable->mItems[index].mKey)
	{
		if (strcmp(pTable->mItems[index].mKey, pKey) == 0)
		{
			return pTable->mItems[index].mValue;
		}

		index = (index + 1) % TABLE_SIZE;

		if (index == originalIndex)
		{
			return NOT_FOUND;
		}
	}

	return NOT_FOUND;
}

// -----------------------------------------------------------------------------

int insert(Table* pTable, const char* pKey, int value)
{
	// this insert tries to handle collisions by linear probing
	int index = hash(pKey);
	int originalIndex = index;

	while (pTable->mItems[index].mKey)
	{
		if (strcmp(pTable->mItems[index].mKey, pKey) == 0)
		{
			return NOT_FOUND;
		}

		index = (index + 1) % TABLE_SIZE;

		if (index == originalIndex)
		{
			return NOT_FOUND;
		}
	}

	pTable->mItems[index].mKey = _strdup(pKey);
	pTable->mItems[index].mValue = value;

	return 0;
}

// -----------------------------------------------------------------------------

int removeKey(Table* pTable, const char* pKey)
{
	// and again linear probing to handle collisions
	int index = hash(pKey);
	int originalIndex = index;

	while (pTable->mItems[index].mKey)
	{
		if (strcmp(pTable->mItems[index].mKey, pKey) == 0)
		{
			free(pTable->mItems[index].mKey);
			pTable->mItems[index].mKey = NULL;
			pTable->mItems[index].mValue = NOT_FOUND;
			return 0;
		}

		index = (index + 1) % TABLE_SIZE;

		if (index == originalIndex)
		{
			return NOT_FOUND;
		}
	}

	return NOT_FOUND;
}

// -----------------------------------------------------------------------------

int main()
{
	Table table;
	initTable(&table);

	insert(&table, "apple", 5);
	printf("apple: %d\n", find(&table, "apple")); // expect 5

	printf("--------------------\n");

	removeKey(&table, "apple");
	printf("apple: %d\n", find(&table, "apple")); // expect -1

	printf("--------------------\n");

	insert(&table, "apple", 5);
	insert(&table, "banana", 10);
	insert(&table, "orange", 15);
	insert(&table, "pear", 20);
	insert(&table, "grape", 25);
	insert(&table, "pineapple", 30);
	insert(&table, "kiwi", 35);

	printf("apple: %d\n", find(&table, "apple")); // expect 5
	printf("banana: %d\n", find(&table, "banana")); // expect 10
	printf("orange: %d\n", find(&table, "orange")); // expect 15
	printf("pear: %d\n", find(&table, "pear")); // expect 20
	printf("grape: %d\n", find(&table, "grape")); // expect 25
	printf("pineapple: %d\n", find(&table, "pineapple")); // expect 30
	printf("kiwi: %d\n", find(&table, "kiwi")); // expect 35

	printf("--------------------\n");

	int i1 = removeKey(&table, "banana");
	int i2 = removeKey(&table, "pear");
	int i3 = removeKey(&table, "pineapple");

	printf("apple: %d\n", find(&table, "apple")); // expect 5
	printf("banana: %d, removed successfully?: %d\n", find(&table, "banana"), i1); // expect -1
	printf("orange: %d\n", find(&table, "orange")); // expect 15
	printf("pear: %d, removed successfully?: %d\n", find(&table, "pear"), i2); // expect -1
	printf("grape: %d\n", find(&table, "grape")); // expect 25
	printf("pineapple: %d, removed successfully?: %d\n", find(&table, "pineapple"), i3); // expect -1
	printf("kiwi: %d\n", find(&table, "kiwi")); // expect 35

	printf("--------------------\n");

	keepWindowOpen();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
