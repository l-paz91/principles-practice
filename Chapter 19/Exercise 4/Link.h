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
	God(string pName) : name(pName) {}
	God(string n, string m, string v, string w)
		: name(n)
		, mythology(m)
		, vehicle(v)
		, weapon(w)
	{}

	string name, mythology, vehicle, weapon;

	// helper functions
	bool operator<(const God& g) { return name < g.name; }
	bool operator==(const God& g) { return g.name == name; }
};

// -----------------------------------------------------------------------------

template <typename T>
class Link
{
public:
	//Link() {}
	Link(T type, Link<T>* p = nullptr, Link<T>* s = nullptr)
		: m_type(type)
		, m_prev(p)
		, m_succ(s)
	{}

	Link<T>* insert(Link<T>* n);
	void addAsSuccesor(Link<T>* n);
	void addOrdered(Link<T>* n);
	void move(Link<T>* n, Link<T>* oldList, Link<T>* newList);
	Link<T>* erase();
	void erase(Link<T>* n);
	Link<T>* find(const T value);
	Link<T>* advance(int n);
	Link<T>* next() const { return m_succ; }
	Link<T>* previous() const { return m_prev; }
	Link<T>* getFirst();

	T getType() const { return m_type; }

private:
	T m_type;
	Link<T>* m_prev;
	Link<T>* m_succ;
};

// -----------------------------------------------------------------------------

template<typename T>
Link<T>* Link<T>::insert(Link<T>* n)
{
	if (n == nullptr)
		return this;
	if (this == nullptr)
		return n;

	// this object comes after n
	n->m_succ = this;

	if (m_prev)
		m_prev->m_succ = n;

	// this objects predecessor becomes n's predecessor
	n->m_prev = m_prev;

	// n becomes this object's predecessor
	m_prev = n;

	return n;
}

// -----------------------------------------------------------------------------

template<typename T>
void Link<T>::addAsSuccesor(Link<T>* n)
{
	if (n == nullptr)
		return;
	if (this == nullptr)
		return;

	if (m_succ)
		insert(n);
	else
	{
		m_succ = n;
		n->m_prev = this;
	}

	n->m_succ = nullptr;
}

// -----------------------------------------------------------------------------

template<typename T>
void Link<T>::addOrdered(Link<T>* n)
{
	Link* temp = this->getFirst();
	while (temp)
	{
		if (n < temp)
		{
			temp->insert(n);
			return;
		}
		if (temp->next())
			temp = temp->advance(1);
		else break;
	}

	temp->addAsSuccesor(n);
	return;
}

// -----------------------------------------------------------------------------

template<typename T>
void Link<T>::move(Link<T>* n, Link<T>* oldList, Link<T>* newList)
{
	if (!n)
		return;

	if (n == oldList)
		oldList = n->next();
	n->erase();

	newList->addOrdered(new Link(n->getType()));
}

// -----------------------------------------------------------------------------

template<typename T>
Link<T>* Link<T>::erase()
{
	if (m_succ)
		m_succ->m_prev = m_prev;
	if (m_prev)
		m_prev->m_succ = m_succ;

	return m_succ;
}

// -----------------------------------------------------------------------------

template<typename T>
void Link<T>::erase(Link<T>* n)
{
	n->erase();
}

// -----------------------------------------------------------------------------

template<typename T>
Link<T>* Link<T>::find(const T value)
{
	Link<T>* temp = this;
	while (temp)
	{
		if (temp->m_type == value)
			return temp;
		temp = temp->m_succ;
	}
	return nullptr;
}

// -----------------------------------------------------------------------------

template<typename T>
Link<T>* Link<T>::advance(int n)
{
	if (this == nullptr)
		return nullptr;

	Link<T>* temp = this;
	if (0 < n)
	{
		while (n--)
		{
			if (temp->m_succ == nullptr)
				return nullptr;
			temp = temp->m_succ;
		}
	}
	else if (n < 0)
	{
		while (n++)
		{
			if (temp->m_prev == nullptr)
				return nullptr;
			temp = temp->m_prev;
		}
	}

	return temp;
}

// -----------------------------------------------------------------------------

template<typename T>
Link<T>* Link<T>::getFirst()
{
	if (Link<T>* temp = this)
	{
		while (temp->m_prev)
			temp = temp->m_prev;
		return temp;
	}

	return nullptr;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !LINK_H_
