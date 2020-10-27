// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "SingleLink.h"

// -----------------------------------------------------------------------------

// always inserts at end
SingleLink* SingleLink::insert(SingleLink* n)
{
	if (n == nullptr)
		return this;
	if (this == nullptr)
		return n;

	SingleLink* temp = this;
	while (temp->next())
	{
		//advance til we find the tail of the list
		temp = temp->next();
	}

	temp->m_succ = n;
	
	return n;
}

// -----------------------------------------------------------------------------

// inserts after a given position
SingleLink* SingleLink::addAtPosition(SingleLink * n, int p)
{
	if (n == nullptr)
		return this;
	if (this == nullptr)
		return n;

	//start at first and advance p, then insert
	SingleLink* temp = advance(p);
	n->m_succ = temp->m_succ;
	temp->m_succ = n;

	return temp;
}

// -----------------------------------------------------------------------------

SingleLink* SingleLink::advance(int n)
{
	if (this == nullptr)
		return nullptr;

	SingleLink* temp = this;
	for (int i = 0; i < n; ++i)
		temp = temp->m_succ;

	return temp;
}

// -----------------------------------------------------------------------------

void SingleLink::erase(SingleLink* n)
{
	// find the previous to n
	SingleLink* temp = this;
	while (temp->next())
	{
		if (temp->next() == n)
			break;
		else
			temp = temp->next();
	}

	if (n->m_succ)
		temp->m_succ = n->m_succ;
	n->m_succ = nullptr;
}

// -----------------------------------------------------------------------------

SingleLink* SingleLink::find(const string& s)
{
	SingleLink* temp = this;
	while (temp)
	{
		if (temp->m_value == s)
			return temp;
		temp = temp->m_succ;
	}
	return nullptr;
}

// -----------------------------------------------------------------------------

SingleLink* SingleLink::next()
{
	return m_succ;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
