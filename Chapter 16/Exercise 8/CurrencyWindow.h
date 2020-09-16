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
