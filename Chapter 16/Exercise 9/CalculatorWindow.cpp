// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "CalculatorWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	CalculatorWindow::CalculatorWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_clearB{ Point{350, 150}, 70, 20, "Clear",
				   [](Address, Address pw) {reference_to<CalculatorWindow>(pw).onClearPressed(); } }
		, m_quitB{ Point{470, 150}, 70, 20, "Quit",
				   [](Address, Address pw) {reference_to<CalculatorWindow>(pw).onQuitPressed(); } }
		, m_inBox{ Point{50, 10}, 200, 20, "Input:" }
		, m_outBox{ Point{350, 50}, 200, 50, "Result:" }
	{
		//this is ridculous
		mv_buttons.push_back(new Button{ Point(50,50), 50, 50, "(",
	[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('('); } });
		mv_buttons.push_back(new Button{ Point(100,50), 50, 50, ")",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress(')'); } });
		mv_buttons.push_back(new Button{ Point(150,50), 50, 50, "%",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('%'); } });
		mv_buttons.push_back(new Button{ Point(200,50), 50, 50, "/",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('/'); } });

		mv_buttons.push_back(new Button{ Point(50,100), 50, 50, "7",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('7'); } });
		mv_buttons.push_back(new Button{ Point(100,100), 50, 50, "8",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('8'); } });
		mv_buttons.push_back(new Button{ Point(150,100), 50, 50, "9",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('9'); } });
		mv_buttons.push_back(new Button{ Point(200,100), 50, 50, "*",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('*'); } });

		mv_buttons.push_back(new Button{ Point(50,150), 50, 50, "4",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('4'); } });
		mv_buttons.push_back(new Button{ Point(100,150), 50, 50, "5",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('5'); } });
		mv_buttons.push_back(new Button{ Point(150,150), 50, 50, "6",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('6'); } });
		mv_buttons.push_back(new Button{ Point(200,150), 50, 50, "-",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('-'); } });

		mv_buttons.push_back(new Button{ Point(50,200), 50, 50, "1",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('1'); } });
		mv_buttons.push_back(new Button{ Point(100,200), 50, 50, "2",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('2'); } });
		mv_buttons.push_back(new Button{ Point(150,200), 50, 50, "3",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('3'); } });
		mv_buttons.push_back(new Button{ Point(200,200), 50, 50, "+",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('+'); } });

		mv_buttons.push_back(new Button{ Point(150,250), 50, 50, "0",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('0'); } });
		mv_buttons.push_back(new Button{ Point(200,250), 50, 50, "=",
			[](Address, Address window) { reference_to<CalculatorWindow>(window).onButtonPress('='); } });

		// attach all buttons to window
		for (Button* b : mv_buttons)
			attach(*b);

		attach(m_clearB);
		attach(m_quitB);
		attach(m_inBox);

		attach(m_outBox);
		m_result = "0";
		m_outBox.put(m_result);
	}

	// -----------------------------------------------------------------------------

	void CalculatorWindow::onButtonPress(char c)
	{
		if (c == '=')
		{
			// have they typed into the box?
			if (m_input.empty())
				m_input = m_inBox.get_string();

			m_input += c;
			// call calculator code here
			m_result = calculate(m_input);
		}
		else
			m_input += c;
		
		m_inBox.put(m_input);

		//display in m_result here
		m_outBox.put(m_result);

		// redraw is needed anytime graphics are changed
		redraw();
	}

	// -----------------------------------------------------------------------------

	void CalculatorWindow::onClearPressed()
	{
		m_input.clear();
		m_inBox.put(m_input);

		m_result = "0";
		m_outBox.put(m_result);

		redraw();
	}

	// -----------------------------------------------------------------------------

	void Graph_lib::CalculatorWindow::onQuitPressed()
	{
		hide();
	}

	// -----------------------------------------------------------------------------

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------