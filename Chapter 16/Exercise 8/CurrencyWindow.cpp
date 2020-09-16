// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "CurrencyWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	CurrencyWindow::CurrencyWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_fakeBackground(Point(0,0), w, h, "background.jpg")
		, m_fromMoneyM{Point(200, 100), 70, 20, Menu::vertical, "from:"}
		, m_toMoneyM{Point(350, 100), 70, 20, Menu::vertical, "to:"}
		, m_inMoney{Point(200, 50), 70, 20, "Amount:"}
		, m_outMoney{Point(350, 50), 70, 20, "Result:"}
		, m_fromCur(GBP)
	{
		attach(m_fakeBackground);
		attach(m_inMoney);
		attach(m_outMoney);

		// create menus
		m_fromMoneyM.attach(new Button{ Point(0,0), 0, 0, "GBP",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).setMoneyFrom(MoneyType::GBP); } });
		m_fromMoneyM.attach(new Button{ Point(0,0), 0, 0, "USD",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).setMoneyFrom(MoneyType::USD); } });
		m_fromMoneyM.attach(new Button{ Point(0,0), 0, 0, "EUR",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).setMoneyFrom(MoneyType::EUR); } });
		m_fromMoneyM.attach(new Button{ Point(0,0), 0, 0, "CAD",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).setMoneyFrom(MoneyType::CAD); } });
		m_fromMoneyM.attach(new Button{ Point(0,0), 0, 0, "AUD",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).setMoneyFrom(MoneyType::AUD); } });		
		attach(m_fromMoneyM);

		m_toMoneyM.attach(new Button{ Point(0,0), 0, 0, "GBP",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).calculateConversion(MoneyType::GBP); } });
		m_toMoneyM.attach(new Button{ Point(0,0), 0, 0, "USD",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).calculateConversion(MoneyType::USD); } });
		m_toMoneyM.attach(new Button{ Point(0,0), 0, 0, "EUR",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).calculateConversion(MoneyType::EUR); } });
		m_toMoneyM.attach(new Button{ Point(0,0), 0, 0, "CAD",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).calculateConversion(MoneyType::CAD); } });
		m_toMoneyM.attach(new Button{ Point(0,0), 0, 0, "AUD",
			[](Address, Address addr) { reference_to<CurrencyWindow>(addr).calculateConversion(MoneyType::AUD); } });
		attach(m_toMoneyM);
		
	}

	// -----------------------------------------------------------------------------

	void CurrencyWindow::setMoneyFrom(MoneyType mt)
	{
		m_fromCur = mt;
	}

	// -----------------------------------------------------------------------------

	void CurrencyWindow::calculateConversion(MoneyType to)
	{
		switch (m_fromCur)
		{
			case GBP:
			{
				switch (to)
				{
					case GBP:
						setRate('£', 1);
						break;
					case USD:
						setRate('$', 2);
						break;
					case EUR:
						setRate('€', 3);
						break;
					case CAD:
						setRate('$', 4);
						break;
					case AUD:
						setRate('$', 5);
						break;						
				}
				break;
			}// end gbp
			
			case USD:
			{
				switch (to)
				{
				case GBP:
					setRate('£', 6);
					break;
				case USD:
					setRate('$', 7);
					break;
				case EUR:
					setRate('€', 8);
					break;
				case CAD:
					setRate('$', 9);
					break;
				case AUD:
					setRate('$', 10);
					break;
				}
			}// end usd

			case EUR:
			{
				switch (to)
				{
				case GBP:
					setRate('£', 11);
					break;
				case USD:
					setRate('$', 12);
					break;
				case EUR:
					setRate('€', 13);
					break;
				case CAD:
					setRate('$', 14);
					break;
				case AUD:
					setRate('$', 15);
					break;
				}
			}// end eur

			case CAD:
			{
				switch (to)
				{
				case GBP:
					setRate('£', 16);
					break;
				case USD:
					setRate('$', 17);
					break;
				case EUR:
					setRate('€', 18);
					break;
				case CAD:
					setRate('$', 19);
					break;
				case AUD:
					setRate('$', 20);
					break;
				}
			}// end cad

			case AUD:
			{
				switch (to)
				{
				case GBP:
					setRate('£', 21);
					break;
				case USD:
					setRate('$', 22);
					break;
				case EUR:
					setRate('€', 23);
					break;
				case CAD:
					setRate('$', 24);
					break;
				case AUD:
					setRate('$', 25);
					break;
				}
			}// end usd
		}
	}

	string CurrencyWindow::getRate(int lineNum)
	{
		ifstream f("ratesData2.txt");
		string s;

		for (int i = 1; i <= lineNum; ++i)
			getline(f, s);

		s.erase(0, 10);

		return s;
	}

	// -----------------------------------------------------------------------------

	void CurrencyWindow::setRate(char cur, int num)
	{
		float rate = stof(getRate(num));
		float f = rate * m_inMoney.get_float();
		ostringstream ss;
		ss << cur << f;
		m_outMoney.put(ss.str());
	}

	// -----------------------------------------------------------------------------

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------