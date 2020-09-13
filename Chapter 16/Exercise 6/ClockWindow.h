// -----------------------------------------------------------------------------
#ifndef CLOCKWINDOW_H_
#define CLOCKWINDOW_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "AnimatedClock.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// ClockWindow is a simple window that displays a clock using the current time

	struct ClockWindow : public Window
	{
	public:
		ClockWindow(Point xy, int w, int h, const char* title);

		void tick();

	private:
		// callbacks
		static void cb_tick(Address addr);

		// objects
		AnimatedClock m_animClock;
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !CLOCKWINDOW_H_
