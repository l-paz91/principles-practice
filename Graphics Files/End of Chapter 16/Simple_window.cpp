
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include "Simple_window.h"

namespace Graph_lib
{
	//------------------------------------------------------------------------------

	Simple_window::Simple_window(Point xy, int w, int h, const char* title)
		: Window(xy, w, h, title)
		, button_pushed(false)
		, next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next)
		, m_xy(xy)
		, m_width(w)
		, m_height(h)
	{
		attach(next_button);
	}

	//------------------------------------------------------------------------------

	bool Simple_window::wait_for_button()
	// modified event loop:
	// handle all events (as per default), quit when button_pushed becomes true
	// this allows graphics without control inversion
	{
		show();
		button_pushed = false;
	#if 1
		// Simpler handler
		while (!button_pushed) 
			Fl::wait();
		
		Fl::redraw();
	#else
		// To handle the case where the user presses the X button in the window frame
		// to kill the application, change the condition to 0 to enable this branch.
		Fl::run();
	#endif
		return button_pushed;
	}

	//------------------------------------------------------------------------------

	void Simple_window::next()
	{
		button_pushed = true;
		hide();
	}

	//------------------------------------------------------------------------------

} //end namespace Graph_lib

