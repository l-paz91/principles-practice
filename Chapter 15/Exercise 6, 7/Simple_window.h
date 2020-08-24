// -----------------------------------------------------------------------------
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

namespace Graph_lib
{
	// Simple_window is basic scaffolding for ultra-simple interaction with graphics
	// it provides one window with one "next" button for ultra-simple animation

	struct Simple_window : Window 
	{
		Simple_window(Point xy, int w, int h, const char* title);

		bool wait_for_button();

		void wait_for_button_modified()
			// modified event loop
			// handle all events (as per default), but quit when button_pushed becomes true
			// this allows graphics without control inversion
		{
			while (!button_pushed) Fl::wait();
			button_pushed = false;
			Fl::redraw();
		}

		Point xy()   const { return m_xy; }
		int width()  const { return m_width; }
		int height() const { return m_height; }

		Button next_button;
	private:
		Point m_xy;
		int m_width, m_height;
		bool button_pushed;

		static void cb_next(Address, Address addr) // callback for next_button
		//	{ reference_to<Simple_window>(addr).next(); }
		{
			static_cast<Simple_window*>(addr)->next();
		}

		void next();
	};

} // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
