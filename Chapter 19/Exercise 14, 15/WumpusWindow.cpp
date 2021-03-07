// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "WumpusWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	WumpusWindow::WumpusWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, mMainMenuB(Point(x_max() - 200,   0), 200, 50, "Main Menu", cb_menu )
		, mRestartB (Point(x_max() - 200,  50), 200, 50, "Restart",   cb_restart)
		, mQuitB    (Point(x_max() - 200, 100), 200, 50, "Quit",      cb_quit)
		, mContinueB(Point(x_max() - 200, 320), 200, 50, "Continue",  cb_continue)
		, mLine1	(Point(x_max() - 200, 0), Point(x_max() - 200, y_max() - 200))
		, mLine2    (Point(0, y_max() - 200), Point(x_max() , y_max() - 200 ))
		, mGameText   (Point(5, 400), 590, 200, "")
		, mInbox (Point(460, 250), 100, 20, "Input: ")
		, mGuess (Point(460, 280), 100, 20, "Guess: ")
		, mGameState(eTITLE)
	{
		attach(mMainMenuB);
		attach(mRestartB);
		attach(mQuitB);
		attach(mContinueB);

		mLine1.set_style(Line_style(Line_style::solid, 3));
		mLine1.set_color(Color::white);
		attach(mLine1);
		mLine2.set_style(Line_style(Line_style::solid, 3));
		mLine2.set_color(Color::white);
		attach(mLine2);

		attach(mGameText);
		mGameText.setSizeColourFont(15);

		attach(mInbox);
		attach(mGuess);
;	}

	// -----------------------------------------------------------------------------

	void WumpusWindow::playGame()
	{
		if(mGameState == eTITLE)
			instructions();
		mGameState = eGETMOVE;
	}

	// -----------------------------------------------------------------------------

	void WumpusWindow::restartPressed()
	{
		for (int i = 0; i < rects.size(); ++i)
			detach(rects[i]);
		rooms.clear(); 
		rects.clear(); 
		cave.initCave(); 
		playGame();
	}

	// -----------------------------------------------------------------------------

	void WumpusWindow::contPressed()
	{
		switch (mGameState)
		{
			case eGETMOVE:
			{	
				for (int i = 0; i < rects.size(); ++i)
					detach(rects[i]);
				rects.clear();
				rooms.clear();
				cave.getNearbyRooms(rooms, mGameText);

				//draw the rooms
				rects.push_back(Rectangle(Point(150, 150), 60, 60));
				for (int i = 0; i < rooms.size(); ++i)
				{
					switch (rooms[i].mDir)
					{
					case eUP:
					{
						Rectangle rect(Point(170, 110), 20, 40);
						rects.push_back(rect);
						break;
					}
					case eDOWN:
					{
						Rectangle rect(Point(170, 210), 20, 40);
						rects.push_back(rect);
						break;
					}
					case eLEFT:
					{
						Rectangle rect(Point(110, 170), 40, 20);
						rects.push_back(rect);
						break;
					}
					case eRIGHT:
					{
						Rectangle rect(Point(210, 170), 40, 20);
						rects.push_back(rect);
						break;
					}
					}
				}
				for (int i = 0; i < rects.size(); ++i)
					attach(rects[i]);
				mGameState = eMOVE;
				redraw();
				break;
			}
			case eMOVE:
			{
				// set the guess
				if (mGuess.get_string() != "")
				{
					char c1;
					uint32_t c2;
					string input = mGuess.get_string();
					c1 = input[0];
					c2 = stoi(input.substr(1, input.size() - 1));
					cave.setGuess(c2, (c1 == 'b') ? eBAT : ePIT);
				}

				mGameState = cave.movePlayer(rooms, mGameText, mInbox, mGameState);
				mInbox.put("");
				mGuess.put("");
				redraw();
				break;
			}
			case eWIN:
			{
				redraw();
				break;
			}
			case eGAMEOVER:
			{
				redraw();
				break;
			}
			case eTITLE:
			{
				instructions();
				mGameState = eGETMOVE;
				break;
			}
		}
	}

	// -----------------------------------------------------------------------------

	void WumpusWindow::instructions()
	{
		stringstream ss;
		ss << "- A rather smelly monster lives deep in the dark cave. It is threatening life as we know it." << endl;
		ss << "- The princess wants you to go and slay the Wumpus. You are the only one that can do it..." << endl;
		ss << "- The cave has two hazards; bottomless pits and giant bats." << endl;
		ss << "- If you enter a room with a pit and you have no planks, it's the end of the game." << endl;
		ss << "- If you enter a room with a bat, it will pick you up and drop you in another room." << endl;
		ss << "- If you enter a room with the wumpus, or he enters yours, he eats you." << endl;
		ss << "- You can hear bats and smell the wumpus. If you feel a breeze, that means there is a pit nearby." << endl;

		ss << "\n---CONTROLS--\n";
		ss << "- To move type 'm' followed by the room number. Example: m13" << endl;
		ss << "- To shoot type 's' followed by the room number. Example: s13" << endl;
		ss << "- To guess a bat or pit type 'b' or 'p' followed by the room number. Example: b13" << endl;
		ss << "\nMaybe other things will happen in the cave...who knows? All those who have ventured in, have not returned..." << endl;
		ss << "It's time to go and Hunt the Wumpus. ";
		ss << "\nPress continue...";
		mGameText.put(ss.str());
	}

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
