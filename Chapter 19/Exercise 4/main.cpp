// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 19 - Exercise 4
/*
	Modify class Link from section 19.9.3 to be a template with the type of value 
	as the template argument. Then redo exercise 13 from Chapter 17 with Link<God>.
*/
// https://github.com/l-paz91/principles-practice/
// -----------------------------------------------------------------------------

//--INCLUDES--//
//#include "std_lib_facilities.h"
#include "Link.h"

// -----------------------------------------------------------------------------

void print_allGods(Link<God>* p)
{
	Link<God>* first = p->getFirst();
	while (first)
	{
		const God g = first->getType();
		cout << "Name: " << g.name << " | Mythology: " << g.mythology << " | Vehicle: " << g.vehicle << " | Weapon: " << g.weapon << endl;
		first = first->next();
	}
}

// -----------------------------------------------------------------------------

void print_all(Link<God>* p)
{
	Link<God>* first = p->getFirst();
	cout << "{";
	while (first)
	{
		cout << first->getType().name;
		if (first = first->next())
			cout << ", ";
	}
	cout << "}" << endl;
}

// -----------------------------------------------------------------------------

int main()
{
	Link<God>* godsList = new Link<God>{ God("Thor", "Norse", "", "Mjolnir") };
	godsList = godsList->insert(new Link<God>{ God("Hera", "Greek", "Peacock Chariot", "Cattle?") });
	godsList = godsList->insert(new Link<God>{ God("Ra", "Egyptian", "Chariot", "The Sun") });
	godsList = godsList->insert(new Link<God>{ God("Odin", "Norse", "Sleipner", "Spear and Gungnir") });
	godsList = godsList->insert(new Link<God>{ God("Zeus", "Greek", "", "Thunderbolt") });
	godsList = godsList->insert(new Link<God>{ God("Osiris", "Egyptian", "", "Crook and Flail") });
	godsList = godsList->insert(new Link<God>{ God("Freia", "Norse", "Cat Chariot", "Brisingamen?") });
	godsList = godsList->insert(new Link<God>{ God("Poseidon", "Greek", "Horse", "Trident") });
	godsList = godsList->insert(new Link<God>{ God("Horus", "Egyptian", "", "Falcon") });
	print_all(godsList);
	cout << endl;

	God thor("Thor", "Norse", "", "Mjolnir");
	Link<God>* norse_gods = new Link<God>(godsList->find(God("Thor"))->getType());
	godsList->erase(godsList->find(God("Thor")));
	godsList->move(godsList->find(God("Odin")), godsList, norse_gods);
	godsList->move(godsList->find(God("Freia")), godsList, norse_gods);

	print_all(norse_gods);
	cout << endl;

	Link<God>* greek_gods = new Link<God>(godsList->find(God("Hera"))->getType());
	godsList->erase(godsList->find(God("Hera")));
	godsList->move(godsList->find(God("Zeus")), godsList, greek_gods);
	godsList->move(godsList->find(God("Poseidon")), godsList, greek_gods);

	print_all(greek_gods);
	cout << endl;

	Link<God>* egyptian_gods = new Link<God>(godsList->find(God("Ra"))->getType());
	godsList->erase(godsList->find(God("Ra")));
	godsList->move(godsList->find(God("Osiris")), godsList, egyptian_gods);
	godsList->move(godsList->find(God("Horus")), godsList, egyptian_gods);

	print_all(egyptian_gods);
	cout << endl;

	keep_window_open();
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
