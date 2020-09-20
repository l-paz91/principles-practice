// -----------------------------------------------------------------------------
#ifndef FUNCTIONWINDOW_H_
#define FUNCTIONWINDOW_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// FunctionWindow

	struct FunctionWindow : public Window
	{
	public:
		FunctionWindow(Point xy, int w, int h, const char* title);

	private:
		// actions
		void onQuitPressed();
		void onButtonPressed(std::function<double(double)>f);

		// objects
		Axis m_xaxis, m_yaxis;
		StoredFct m_function;
		In_box m_range1, m_range2;
		Button m_quitB, m_sinB, m_cosB, m_tanB, m_logB;
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------



#endif // !FUNCTIONWINDOW_H_

