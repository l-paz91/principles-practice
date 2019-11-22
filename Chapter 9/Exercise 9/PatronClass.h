// ---------------------------------------------------------------------------//
// PatronClass.h
// ---------------------------------------------------------------------------//
#ifndef _PATRONCLASS_H_

//--INCLUDES--//
#include "BookClass.h"

//--GLOBALS--//
extern uint32_t uniqueCardNum;
uint32_t createCardNumber();

// -----------------------------------------------------------------------------

class Patron
{
public:
	Patron(string name) : m_name(name), m_fees(0.0), m_cardNumber(createCardNumber()) {}
	~Patron() {}

	string getName() const { return m_name; }
	uint32_t getCardNum() const { return m_cardNumber; }
	double getFees() const { return m_fees; }

	void setName(string name) { m_name = name; }
	void setCardNumber(uint32_t cardNum) { m_cardNumber = cardNum; }
	void setFees(double fee) { m_fees = fee; }
	bool owesFees() const { return m_fees > 0.0f; }

private:
	string m_name;
	double m_fees;
	uint32_t m_cardNumber;
};

bool operator==(const Patron& p1, const Patron& p2);
ostream& operator<<(ostream& os, const Patron& p);

#endif // !_PATRONCLASS_H_

