// -----------------------------------------------------------------------------
#ifndef WUMPUSWINDOW_H_
#define WUMPUSWINDOW_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "Cave.h"
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	// 

	struct WumpusWindow : public Window
	{
	public:
		WumpusWindow(Point xy, int w, int h, const char* title);

		void playGame();

	private:
		// actions
		void menuPressed() { mGameState = eTITLE; restartPressed(); }
		void restartPressed();
		void quitPressed() { hide(); }
		void contPressed();

		void instructions();

		// callbacks
		static void cb_menu(Address, Address addr) { reference_to<WumpusWindow>(addr).menuPressed(); }
		static void cb_restart(Address, Address addr) { reference_to<WumpusWindow>(addr).restartPressed(); }
		static void cb_quit(Address, Address addr) { reference_to<WumpusWindow>(addr).quitPressed(); }
		static void cb_continue(Address, Address addr) { reference_to<WumpusWindow>(addr).contPressed(); }

		// objects
		Button mMainMenuB;
		Button mRestartB;
		Button mQuitB;
		Button mContinueB;

		Line mLine1;
		Line mLine2;

		Multiline_Outbox mGameText;
		In_box mInbox;
		In_box mGuess;

		vector<Rectangle> rects;
		vector<CodeHelp::Vector2D> rooms;

		// -----------------------------------------------------------------------------

		Cave cave;
		GameState mGameState;
	};

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif // !WUMPUSWINDOW_H_
