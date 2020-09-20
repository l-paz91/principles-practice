// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "FunctionWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	FunctionWindow::FunctionWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_xaxis(Axis::x, Point(100, 300), 400, 400/20, "x")
		, m_yaxis(Axis::y, Point(300, 500), 400, 400/20, "y")
		, m_function(static_cast<double(*)(double)>(log), -10, 11, Point(300, 300), 400, 20, 20)
		, m_range1(Point(70, 0), 70, 20, "Range 1:")
		, m_range2(Point(210, 0), 70, 20, "Range 2:")
		, m_quitB(Point(x_max()-70, 0), 70, 20, "Quit",
			[](Address, Address addr) {reference_to<FunctionWindow>(addr).onQuitPressed(); })
		, m_sinB(Point(0, y_max()-20), 70, 20, "Sin",
			[](Address, Address addr) {reference_to<FunctionWindow>(addr).onButtonPressed(static_cast<double(*)(double)>(sin)); })
		, m_cosB(Point(70, y_max()-20), 70, 20, "Cos",
			[](Address, Address addr) {reference_to<FunctionWindow>(addr).onButtonPressed(static_cast<double(*)(double)>(cos)); })
		, m_tanB(Point(140, y_max() - 20), 70, 20, "Tan",
			[](Address, Address addr) {reference_to<FunctionWindow>(addr).onButtonPressed(static_cast<double(*)(double)>(tan)); })
		, m_logB(Point(210, y_max() - 20), 70, 20, "Log",
			[](Address, Address addr) {reference_to<FunctionWindow>(addr).onButtonPressed(static_cast<double(*)(double)>(log)); })
	{
		attach(m_xaxis);
		attach(m_yaxis);

		m_function.set_color(Color::blue);
		attach(m_function);

		attach(m_range1);
		m_range1.put("-10");
			
		attach(m_range2);
		m_range2.put("11");

		attach(m_quitB);
		attach(m_sinB);
		attach(m_cosB);
		attach(m_tanB);
		attach(m_logB);
	}

	// -----------------------------------------------------------------------------

	void FunctionWindow::onQuitPressed()
	{
		hide();
	}

	// -----------------------------------------------------------------------------

	void FunctionWindow::onButtonPressed(std::function<double(double)> f)
	{
		int range1 = m_range1.get_int();
		int range2 = m_range2.get_int();

		if (range1 <= -100 || range2 <= -100)
			error("bad ranges");
		else
			m_function.init(f, range1, range2, Point(300, 300), 400, 20, 20);

		redraw();
	}

	// -----------------------------------------------------------------------------



}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------