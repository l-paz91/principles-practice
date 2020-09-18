// -----------------------------------------------------------------------------
#ifndef CALCULATORWINDOW_H_
#define CALCULATORWINDOW_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "Calculator.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// 

	struct CalculatorWindow : public Window
	{
	public:
		CalculatorWindow(Point xy, int w, int h, const char* title);

	private:
		// actions	
		void onClearPressed();
		void onQuitPressed();
		void onButtonPress(char c);

		// objects
		vector<Button*> mv_buttons;
		Button m_clearB, m_quitB;
		In_box m_inBox;
		Out_box m_outBox;
		string m_input, m_result;


	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !CALCULATORWINDOW_H_