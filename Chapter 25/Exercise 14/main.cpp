// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 25 - Exercise 14

	Implement a simple vector that can hold at most N elements allocated from a pool. 
	Test of for N === 1000 and integer elements.

	I'm using a modified vector implementation created from Chapter 19 - Exercise 8
  Original version:
	https://github.com/l-paz91/principles-practice/tree/master/Chapter%2019/Exercise%208%2C%209

*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "MyVector.h"

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

int main()
{
	const int numberElementsRequired = 10;
	const int maxAllocationSpaceRequired = 1000;

	MyVector<int> myVector(maxAllocationSpaceRequired, numberElementsRequired);
	cout << "Number of elements: " << myVector.size() << '\n';
	cout << "Space allocated: " << myVector.maxCapacity() << '\n';

	// should print 10 zeroes
	for (int i = 0; i < myVector.size(); ++i)
	{
		cout << myVector[i] << ", ";
	}

	// this will error as MyVector has range checks on it size
	//cout << myVector[100] << '\n';

	for (int i = 0; i < 500; ++i)
	{
		myVector.pushBack(i);
	}

	cout << "\nNumber of elements: " << myVector.size() << '\n';
	cout << "Space allocated: " << myVector.maxCapacity() << '\n';
	cout << "myVector[500]: " << myVector[500] << '\n';

	cout << "\n\n";
	pressKeyToContinue();
	_CrtDumpMemoryLeaks();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
