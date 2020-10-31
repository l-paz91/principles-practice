// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 17 - Exercise 14
/*
	Could the "list of gods" example from Section 17.10.1 have been written using 
	a singly-linked list; that is,could we have left the prev member out of Link? 
	Why might we want to do that? For what kind of examples would it make sense to 
	use a singly-linked list? Re-implement that example using only a singly-linked 
	list.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Link.h"

// -----------------------------------------------------------------------------

void print_all(SingleLink* p)
{
	SingleLink* first = p;
	cout << "{";
	while (first)
	{
		cout << first->getName();
		if (first = first->next())
			cout << ", ";
	}
	cout << "}" << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	SingleLink* norse_gods = new SingleLink{ God("Thor") };
	norse_gods->insert(new SingleLink{ God("Odin") });
	norse_gods->insert(new SingleLink{ God("Zeus") });
	norse_gods->insert(new SingleLink{ God("Freia") });

	SingleLink* greek_gods = new SingleLink{ God("Hera") };
	greek_gods->insert(new SingleLink{ God("Athena") });
	greek_gods->insert(new SingleLink{ God("Mars") });
	greek_gods->insert(new SingleLink{ God("Poseidon") });

	//print out the lists
	print_all(norse_gods);
	print_all(greek_gods);

	// correct name of god of war
	SingleLink* p = greek_gods->find("Mars");
	if (p)
		p->setName("Ares");

	// move zeus to correct pantheon
	SingleLink* p2 = norse_gods->find("Zeus");
	if (p2)
	{
		if (p2 == norse_gods)
			norse_gods = p2->next();
		norse_gods->erase(p2);
		greek_gods->insert(p2);
	}

	//print out the lists
	print_all(norse_gods);
	print_all(greek_gods);

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
