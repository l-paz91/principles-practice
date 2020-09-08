// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "My_window.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	My_window::My_window(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_nextB(Point(x_max() - 140, 0), 70, 20, "Next", cb_nextB)
		, m_quitB(Point(x_max() - 70, 0), 70, 20, "Quit", cb_quitB)
		, m_randMoveB(Point(randint(0, x_max()-100), randint(0, y_max()-100)), 100, 100, "", 
			[](Address, Address addr) {reference_to<My_window>(addr).randMoveBPressed(); })
		, m_randImage(Point(m_randMoveB.loc), "doge2.jpg")
	{
		attach(m_nextB);
		attach(m_quitB);
		attach(m_randMoveB);
		attach(m_randImage);
	}

	// -----------------------------------------------------------------------------

	void My_window::waitForNext()
	{
		Fl::wait();
	}

	// -----------------------------------------------------------------------------

	void My_window::nextPressed()
	{
		Fl::redraw();		
	}

	// -----------------------------------------------------------------------------

	void My_window::quitPressed()
	{
		hide();		// fltk idiom to delete window
	}

	// -----------------------------------------------------------------------------

	void My_window::randMoveBPressed()
	{
		Point newPoint{ double(randint(0, x_max()-100)), double(randint(0, y_max()-100)) };
		m_randMoveB.move(newPoint.x, newPoint.y);
		m_randImage.set_point(0, newPoint);

		redraw();
	}

	// -----------------------------------------------------------------------------

	void My_window::cb_nextB(Address, Address addr)
	{
		static_cast<My_window*>(addr)->nextPressed();
	}

	// -----------------------------------------------------------------------------

	void My_window::cb_quitB(Address, Address addr)
	{
		static_cast<My_window*>(addr)->quitPressed();
	}

	// -----------------------------------------------------------------------------

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
