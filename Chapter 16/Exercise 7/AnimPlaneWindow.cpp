// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "AnimPlaneWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	AnimPlaneWindow::AnimPlaneWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_startB(Point(x_max() - 210, 0), 70, 20, "Start", cb_startB)
		, m_stopB(Point(x_max() - 140, 0), 70, 20, "Stop", cb_stopB)
		, m_quitB(Point(x_max() - 70, 0), 70, 20, "Quit",
			[](Address, Address addr) { reference_to<AnimPlaneWindow>(addr).quitPressed(); })
		, m_animPlane(x_max()/2, y_max()/2)
	{
		attach(m_startB);
		attach(m_stopB);
		attach(m_quitB);
		attach(m_animPlane);
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::tick()
	{
		m_animPlane.tick();
		redraw();
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::startPressed()
	{
		// register tick function
		Fl::add_timeout(0.05, cb_tick, (void*)this);
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::stopPressed()
	{
		//remove the tick function
		Fl::remove_timeout(cb_tick, (void*)this);
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::quitPressed()
	{
		hide();
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::cb_tick(Address addr)
	{
		static_cast<AnimPlaneWindow*>(addr)->tick();
		Fl::repeat_timeout(0.05, cb_tick, (void*)addr);
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::cb_startB(Address, Address addr)
	{
		static_cast<AnimPlaneWindow*>(addr)->startPressed();
	}

	// -----------------------------------------------------------------------------

	void AnimPlaneWindow::cb_stopB(Address, Address addr)
	{
		static_cast<AnimPlaneWindow*>(addr)->stopPressed();
	}

	// -----------------------------------------------------------------------------

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------