// -----------------------------------------------------------------------------
#ifndef ANIMPLANEWINDOW_H_
#define ANIMPLANEWINDOW_H_

// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "AnimPlane.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// AnimPlaneWindow is a simple window with three buttons; Stop, Start and quit
	// stop and start control a 1 second timer

	struct AnimPlaneWindow : public Window
	{
	public:
		AnimPlaneWindow(Point xy, int w, int h, const char* title);

	private:
		// actions
		void tick();
		void startPressed();
		void stopPressed();
		void quitPressed();

		// callbacks
		static void cb_tick(Address addr);
		static void cb_startB(Address, Address addr);
		static void cb_stopB(Address, Address addr);

		// objects
		Button m_startB;
		Button m_stopB;
		Button m_quitB;
		AnimPlane m_animPlane;
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


#endif // !ANIMPLANEWINDOW_H_

