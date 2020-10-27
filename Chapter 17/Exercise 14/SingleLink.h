// -----------------------------------------------------------------------------
#ifndef SINGLELINK_H_
#define SINGLELINK_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct God
{
	God() {}
	God(string n, string m = "", string v = "", string w = "")
		: name(n)
		, mythology(m)
		, vehicle(v)
		, weapon(w)
	{}

	string name, mythology, vehicle, weapon;
};

// -----------------------------------------------------------------------------

class SingleLink
{
public:
	SingleLink(God g, SingleLink* p = nullptr, SingleLink* s = nullptr)
		: m_god(g)
		, m_value(g.name)
		, m_succ(s)
	{}

	SingleLink* insert(SingleLink* n);
	SingleLink* addAtPosition(SingleLink* n, int p);
	SingleLink* advance(int n);
	void erase(SingleLink* n);
	SingleLink* find(const string& s);
	SingleLink* next();
	string getName() { return m_god.name; }
	void setName(string n) { m_god.name = n; }

private:
	God m_god;
	SingleLink* m_succ;
	string m_value;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !SINGLELINK_H_
