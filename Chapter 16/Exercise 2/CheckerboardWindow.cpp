// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "CheckerboardWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	CheckerboardWindow::CheckerboardWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_quitB{ Point{double(x_max() - 70), 0}, 70, 20, "Quit",
				   [](Address, Address pw) {reference_to<CheckerboardWindow>(pw).onQuitPressed(); } }
		, m_xyOut{ Point{50, 0}, 70, 20, "(x,y):" }
		, m_previous(-1)
	{
		mv_buttons.push_back(new Button { Point(50,50), 50, 50, "1", 
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(0); } });
		mv_buttons.push_back(new Button{ Point(100,50), 50, 50, "2",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(1); } });
		mv_buttons.push_back(new Button{ Point(150,50), 50, 50, "3",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(2); } });
		mv_buttons.push_back(new Button{ Point(200,50), 50, 50, "4",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(3); } });
		
		mv_buttons.push_back(new Button{ Point(50,100), 50, 50, "5",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(4); } });
		mv_buttons.push_back(new Button{ Point(100,100), 50, 50, "6",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(5); } });
		mv_buttons.push_back(new Button{ Point(150,100), 50, 50, "7",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(6); } });
		mv_buttons.push_back(new Button{ Point(200,100), 50, 50, "8",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(7); } });
		
		mv_buttons.push_back(new Button{ Point(50,150), 50, 50, "9",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(8); } });
		mv_buttons.push_back(new Button{ Point(100,150), 50, 50, "10",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(9); } });
		mv_buttons.push_back(new Button{ Point(150,150), 50, 50, "11",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(10); } });
		mv_buttons.push_back(new Button{ Point(200,150), 50, 50, "12",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(11); } });
		
		mv_buttons.push_back(new Button{ Point(50,200), 50, 50, "13",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(12); } });
		mv_buttons.push_back(new Button{ Point(100,200), 50, 50, "14",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(13); } });
		mv_buttons.push_back(new Button{ Point(150,200), 50, 50, "15",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(14); } });
		mv_buttons.push_back(new Button{ Point(200,200), 50, 50, "16",
			[](Address, Address window) { reference_to<CheckerboardWindow>(window).onButtonPress(15); } });	

		// attach all buttons to window
		for (Button* b : mv_buttons)
			attach(*b);

		attach(m_quitB);
		attach(m_xyOut);
	}

	// -----------------------------------------------------------------------------

	void CheckerboardWindow::onButtonPress(int i)
	{
		// turn the button a different colour when pressed
		mv_buttons[i]->setColor(Color::green);

		// if its the first button press, assign prev button now
		if (m_previous == -1)
			m_previous = i;
		else
			// else set the prev button back to the background colour
			mv_buttons[m_previous]->setColor(Color::background);

		// print out coords of button pressed
		Point xy = mv_buttons[i]->loc;
		ostringstream ss;
		ss << xy.x << ',' << xy.y;
		m_xyOut.put(ss.str());

		// set current as previous
		m_previous = i;

		// redraw is needed anytime graphics are changed
		redraw();
	}

	// -----------------------------------------------------------------------------

	void CheckerboardWindow::onQuitPressed()
	{
		hide();		// fltk idiom to delete window
	}

	// -----------------------------------------------------------------------------

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
