// -----------------------------------------------------------------------------
#ifndef LINK_H_
#define LINK_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct God
{
	God() {}
	God(string n, string m, string v, string w)
		: name(n)
		, mythology(m)
		, vehicle(v)
		, weapon(w)
	{}

	string name, mythology, vehicle, weapon;
};

// -----------------------------------------------------------------------------

class Link
{
public:
	//Link() {}
	Link(God g, Link* p = nullptr, Link* s = nullptr)
		: m_god(g)
		, m_value(g.name)
		, m_prev(p)
		, m_succ(s)
	{}

	Link* insert(Link* n);
	void addAsSuccesor(Link* n);
	void addOrdered(Link* n);
	void move(Link* n, Link* oldList, Link* newList);
	Link* erase();
	void erase(Link* n);
	Link* find(const string& s);
	const Link* find(const string& s) const;
	Link* advance(int n);
	Link* next() const { return m_succ; }
	Link* previous() const { return m_prev; }
	Link* getFirst();
	string getName() const { return m_value; }
	void setName(string value) { m_value = value; }
	
	God getGod() const { return m_god; }

private:
	God m_god;
	Link* m_prev;
	Link* m_succ;

	string m_value;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !LINK_H_
