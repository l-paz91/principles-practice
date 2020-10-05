// -----------------------------------------------------------------------------
#ifndef LINK_H_
#define LINK_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

class Link
{
public:
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		: m_value(v)
		, m_prev(p)
		, m_succ(s)
	{}

	Link* insert(Link* n);
	Link* add(Link* n);
	Link* erase();
	Link* find(const string& s);
	const Link* find(const string& s) const;
	Link* advance(int n) const;
	Link* next() const { return m_succ; }
	Link* previous() const { return m_prev; }
	string getName() const { return m_value; }
	void setName(string value) { m_value = value; }

private:
	Link* m_prev;
	Link* m_succ;

	string m_value;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !LINK_H_
