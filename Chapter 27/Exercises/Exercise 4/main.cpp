// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 27 - Exercise 4

	If you didn't already, write a C++ version of the intrusive List example in 
	section 27.9 and test it using every function.
*/
// https://github.com/l-paz91/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "IntrusiveList.h"

#include <conio.h>
#include <crtdbg.h>
#include <iostream>

using namespace std;

// -----------------------------------------------------------------------------

inline void pressKeyToContinue()
{
	cin.clear();
	cout << "Press any key to continue\n";
	_getch();
	return;
}

// -----------------------------------------------------------------------------

struct Name
{
	Name(const string& pName)
		: mName(pName)
	{}

	string mName;
};

// -----------------------------------------------------------------------------

// print an intrusive list of names
void printNames(IntrusiveList<Name>& pNames)
{
	// print the names
	IntrusiveListLink<Name>* current = pNames.mFirst;
	while (current)
	{
		cout << current->mData.mName << endl;
		current = current->mNext;
	}

	cout << "\n---------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------

void fct()
{
	// make a list of names
	IntrusiveList<Name> names;

	// ---- add some names
	cout << "Add some names:\n";
	names.pushBack(new IntrusiveListLink<Name>(Name("Norah")));
	names.pushBack(new IntrusiveListLink<Name>(Name("Annemarie")));
	names.pushBack(new IntrusiveListLink<Name>(Name("Kris")));

	printNames(names);

	// ---- test erase - remove the second name
	cout << "\nRemove the second name:\n";
	names.erase(names.getLinkAt(1));

	printNames(names);

	// ---- test pushFront
	cout << "\nAdd names to the front:\n";
	names.pushFront(new IntrusiveListLink<Name>(Name("John")));
	names.pushFront(new IntrusiveListLink<Name>(Name("Jane")));

	printNames(names);

	cout << "Add names to the back:\n";
	names.pushBack(new IntrusiveListLink<Name>(Name("Bob")));
	names.pushBack(new IntrusiveListLink<Name>(Name("Alice")));

	printNames(names);

	// ---- test insert and get link at - Mary should be inserted before Bob
	cout << "\nInsert Mary before Bob:\n";
	names.insert(names.getLinkAt(4), new IntrusiveListLink<Name>(Name("Mary")));

	printNames(names);
}

// -----------------------------------------------------------------------------

int main()
{
	fct();
	_CrtDumpMemoryLeaks();

	pressKeyToContinue();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
