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

Link* Link::add(Link* n)
{
	// much like insert

	return nullptr;
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

Link* Link::advance(int n) const
{
	Link* temp = const_cast<Link*>(this);
	if (temp == nullptr)
		return nullptr;
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
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
