// -----------------------------------------------------------------------------
#ifndef CHECKERBOARDWINDOW_H_
#define CHECKERBOARDWINDOW_H_

//----INCLUDES----//
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// CheckerboardWindow is a simple window with a 4-by-4 checkerboard of buttons
	// these buttons perform simple actions when pressed

	struct CheckerboardWindow : public Window
	{
		CheckerboardWindow(Point xy, int w, int h, const char* title);

	private:
		// button actions
		void onButtonPress(int i);
		void onQuitPressed();

		// member variables
		vector<Button*> mv_buttons;
		Button m_quitB;
		Out_box m_xyOut;
		int m_previous;
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !CHECKERBOARDWINDOW_H_

