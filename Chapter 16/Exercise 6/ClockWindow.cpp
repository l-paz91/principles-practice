// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "ClockWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	ClockWindow::ClockWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_animClock(Point(0, 0), "wallClock.jpg")
	{
		// add the tick function to Fltk's "callback system"
		Fl::add_timeout(1.0, cb_tick, (void*)this);
		
		attach(m_animClock);
	}

	// -----------------------------------------------------------------------------

	void ClockWindow::tick()
	{
		m_animClock.tick();
		redraw();
	}

	void ClockWindow::cb_tick(Address addr)
	{
		static_cast<ClockWindow*>(addr)->tick();
		Fl::repeat_timeout(1.0, cb_tick, (void*)addr);
	}


}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
