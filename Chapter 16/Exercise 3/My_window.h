// -----------------------------------------------------------------------------
#ifndef MY_WINDOW_H
#define MY_WINDOW_H
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------
	
	// My_window is a simple window with two buttons; Next and Quit

	struct My_window : public Window
	{
	public:
		My_window(Point xy, int w, int h, const char* title);

		void waitForNext();

		Point	xy()	 const { return m_xy; }
		int		width()  const { return m_width; }
		int		height() const { return m_height; }

	private:
		// actions
		void nextPressed();
		void quitPressed();
		void randMoveBPressed();

		// callbacks
		static void cb_nextB(Address, Address addr);
		static void cb_quitB(Address, Address addr);

		// objects
		Button m_nextB;
		Button m_quitB;
		Button m_randMoveB;		// button that moves about the screen randomly
		Image  m_randImage;		// image that is attached to Button

		// member variables
		Point m_xy;
		int m_width, m_height;
		
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // MY_WINDOW_H
