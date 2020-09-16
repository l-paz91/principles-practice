// -----------------------------------------------------------------------------
#ifndef CURRENCYWINDOW_H_
#define CURRENCYWINDOW_H_

// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"


// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	struct Rates
	{
		double gbp2usd, gbp2eur, gbp2cad, gbp2aud;

	};


	// CurrencyWindow is a simple window that converts 5 types of currencies

	struct CurrencyWindow : public Window
	{
	public:
		CurrencyWindow(Point xy, int w, int h, const char* title);

	private:
		enum MoneyType {
			GBP, USD, EUR, CAD, AUD
		};

		// actions
		void setMoneyFrom(MoneyType mt);
		void calculateConversion(MoneyType to);
		string getRate(int lineNum);
		void setRate(char cur, int num);

		// callbacks
		static void cb_nextB(Address, Address addr);
		static void cb_quitB(Address, Address addr);

		// objects
		FakeBkg m_fakeBackground;
		Menu m_fromMoneyM, m_toMoneyM;
		In_box m_inMoney;
		Out_box m_outMoney;
		MoneyType m_fromCur;
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !CURRENCYWINDOW_H_