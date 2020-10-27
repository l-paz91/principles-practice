// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "Link.h"

// -----------------------------------------------------------------------------

Link* Link::insert(Link* n)
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

void Link::addAsSuccesor(Link* n)
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

// assumes the list is already in "name" order
// first letter must be upper case because reasons
void Link::addOrdered(Link* n)
{
	Link* temp = this->getFirst();
	while (temp)
	{
		if (n->getName() < temp->getName())
		{
			temp->insert(n);
			return;
		}
		if(temp->next())
			temp = temp->advance(1);
		else break;
	}

	temp->addAsSuccesor(n);
	return;
}

// -----------------------------------------------------------------------------

void Link::move(Link* n, Link* oldList, Link* newList)
{
	if (!n)
		return;

	if (n == oldList)
		oldList = n->next();
	n->erase();
	
	newList->addOrdered(new Link(n->getGod()));
}

// -----------------------------------------------------------------------------

Link* Link::erase()
{
	if (m_succ)
		m_succ->m_prev = m_prev;
	if (m_prev)
		m_prev->m_succ = m_succ;

	return m_succ;
}

// -----------------------------------------------------------------------------

void Link::erase(Link* n)
{
	n->erase();
}

// -----------------------------------------------------------------------------

Link * Link::find(const string & s)
{
	Link* temp = this;
	while (temp)
	{
		if (temp->m_value == s)
			return temp;
		temp = temp->m_succ;
	}
	return nullptr;
}

// -----------------------------------------------------------------------------

const Link* Link::find(const string& s) const
{
	return nullptr;
}

// -----------------------------------------------------------------------------

Link* Link::advance(int n)
{
	if (this == nullptr)
		return nullptr;

	Link* temp = this;
	if (0 < n)
	{
		while (n--)
		{
			if (temp->m_succ == nullptr)
				return nullptr;
			temp = temp->m_succ;
		}
	}
	else if(n < 0)
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

Link* Link::getFirst()
{
	if (Link* temp = this)
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
