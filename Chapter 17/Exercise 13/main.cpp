// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 17 - Exercise 13
/*
	Modify the Link class from section 17.10.1 to hold a value of a struct God. 
	struct God should have members of type string: name, mythology, vehicle, and 
	weapon. For example, God{"Zeus", "Greek", "", "lightning"} and God{"Odin", 
	"Norse", "Eight-legged flying horse called Sleipner", "Spear and Gungnir"}.
	Write a print_all() function that lists gods with their attributes one per line. 
	Add a member function add_ordered() that places its new element in its correct 
	lexicographical position. Using the Links with the values of type God, make a 
	list of gods from three mythologies; then move the elements (gods) from that 
	list to three lexicographically ordered lists - one for each mythology.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Link.h"

// -----------------------------------------------------------------------------

void print_allGods(Link* p)
{
	Link* first = p->getFirst();
	while (first)
	{
		const God g = first->getGod();
		cout << "Name: " << g.name << " | Mythology: " << g.mythology << " | Vehicle: " << g.vehicle << " | Weapon: " << g.weapon << endl;
		first = first->next();
	}
}

// -----------------------------------------------------------------------------

void print_all(Link* p)
{
	Link* first = p->getFirst();
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
	Link* godsList = new Link{ God("Thor", "Norse", "", "Mjolnir") };
	godsList = godsList->insert(new Link{ God("Hera", "Greek", "Peacock Chariot", "Cattle?") });
	godsList = godsList->insert(new Link{ God("Ra", "Egyptian", "Chariot", "The Sun") });
	godsList = godsList->insert(new Link{ God("Odin", "Norse", "Sleipner", "Spear and Gungnir") });
	godsList = godsList->insert(new Link{ God("Zeus", "Greek", "", "Thunderbolt") });
	godsList = godsList->insert(new Link{ God("Osiris", "Egyptian", "", "Crook and Flail") });
	godsList = godsList->insert(new Link{ God("Freia", "Norse", "Cat Chariot", "Brisingamen?") });
	godsList = godsList->insert(new Link{ God("Poseidon", "Greek", "Horse", "Trident") });
	godsList = godsList->insert(new Link{ God("Horus", "Egyptian", "", "Falcon") });
	print_all(godsList);
	cout << endl;

	Link* norse_gods = new Link(godsList->find("Thor")->getGod());
	godsList->erase(godsList->find("Thor"));
	godsList->move(godsList->find("Odin"), godsList, norse_gods);
	godsList->move(godsList->find("Freia"), godsList, norse_gods);

	print_all(norse_gods);
	cout << endl;

	Link* greek_gods = new Link(godsList->find("Hera")->getGod());
	godsList->erase(godsList->find("Hera"));
	godsList->move(godsList->find("Zeus"), godsList, greek_gods);
	godsList->move(godsList->find("Poseidon"), godsList, greek_gods);

	print_all(greek_gods);
	cout << endl;

	Link* egyptian_gods = new Link(godsList->find("Ra")->getGod());
	godsList->erase(godsList->find("Ra"));
	godsList->move(godsList->find("Osiris"), godsList, egyptian_gods);
	godsList->move(godsList->find("Horus"), godsList, egyptian_gods);

	print_all(egyptian_gods);
	cout << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
