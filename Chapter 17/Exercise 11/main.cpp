// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 17 - Exercise 11, 12
/*
	11. Complete the "list of gods" example from section 17.10.1 and run it.
	12. Why did we define two versions of find().
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Link.h"

// -----------------------------------------------------------------------------

void print_all(Link* p)
{
	cout << "{";
	while (p)
	{
		cout << p->getName();
		if (p = p->next())
			cout << ", ";
	}
	cout << "}" << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_gods = new Link{ "Hera" };
	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	// correct name of god of war
	Link* p = greek_gods->find("Mars");
	if (p)
		p->setName("Ares");

	// move zeus to correct pantheon
	Link* p2 = norse_gods->find("Zeus");
	if (p2)
	{
		if (p2 == norse_gods)
			norse_gods = p2->next();
		p2->erase();
		greek_gods = greek_gods->insert(p2);
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
