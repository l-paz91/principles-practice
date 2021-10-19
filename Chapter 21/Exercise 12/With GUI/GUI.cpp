//------------------------------------------------------------------------------
#include "GUI.h"

//------------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------
	
	void FakeBkg::attach(Window& win)
	{
		pw = new Fl_Box(loc.x, loc.y, width, height);
		pw->image(m_image);
		own = &win;
	}

	// -----------------------------------------------------------------------------

	void Button::attach(Window& win)
	{
		pw = new Fl_Button(loc.x, loc.y, width, height, label.c_str());
		pw->callback(reinterpret_cast<Fl_Callback*>(do_it), &win); // pass the window
		own = &win;
	}

	//------------------------------------------------------------------------------

	int In_box::get_int()
	{
		Fl_Input& pi = reference_to<Fl_Input>(pw);
		//	return atoi(pi.value());
		const char* p = pi.value();
		if (!isdigit(p[0]) && p[0] != '-') 
			return -999999;

		//if it's a negative number, make sure it correctly coverts it
		int p2 = atoi(p);
		return p2;
	}

	// -----------------------------------------------------------------------------

	float In_box::get_float()
	{
		Fl_Input& pi = reference_to<Fl_Input>(pw);
		const char* p = pi.value();
		if (!isdigit(p[0])) return -999999;
		return atof(p);
	}

	//------------------------------------------------------------------------------

	string In_box::get_string()
	{
		Fl_Input& pi = reference_to<Fl_Input>(pw);
		return string(pi.value());
	}

	// -----------------------------------------------------------------------------

	void In_box::put(const string& s)
	{
		Fl_Output& po = reference_to<Fl_Output>(pw);
		std::stringstream ss;
		ss << s;
		po.value(ss.str().c_str());
	}

	//------------------------------------------------------------------------------

	void In_box::attach(Window& win)
	{
		pw = new Fl_Input(loc.x, loc.y, width, height, label.c_str());
		own = &win;
	}

	//------------------------------------------------------------------------------

	void Out_box::put(int i)
	{
		Fl_Output& po = reference_to<Fl_Output>(pw);
		std::stringstream ss;
		ss << i;
		po.value(ss.str().c_str());
	}

	//------------------------------------------------------------------------------

	void Out_box::put(const string& s)
	{
		reference_to<Fl_Output>(pw).value(s.c_str());
	}

	//------------------------------------------------------------------------------

	void Out_box::attach(Window& win)
	{
		pw = new Fl_Output(loc.x, loc.y, width, height, label.c_str());
		own = &win;
	}

	//------------------------------------------------------------------------------

	void Multiline_Outbox::setSizeColourFont(int pSize, Fl_Color pColour, Fl_Font pFont)
	{
		reference_to<Fl_Multiline_Output>(pw).textsize(pSize);
		reference_to<Fl_Multiline_Output>(pw).textcolor(pColour);
		reference_to<Fl_Multiline_Output>(pw).textfont(pFont);
	}

	// -----------------------------------------------------------------------------

	void Multiline_Outbox::put(const string& s)
	{
		reference_to<Fl_Multiline_Output>(pw).value(s.c_str());
	}

	// -----------------------------------------------------------------------------

	void Multiline_Outbox::attach(Window & win)
	{
		pw = new Fl_Multiline_Output(loc.x, loc.y, width, height, label.c_str());
		own = &win;
	}

	// -----------------------------------------------------------------------------

	void MultilineScroll_Outbox::setSizeColourFont(int pSize /*= 16*/, Fl_Color pColour /*= Color::black*/, Fl_Font pFont /*= Font::screen*/)
	{
		reference_to<Fl_Text_Display>(pw).textsize(pSize);
		reference_to<Fl_Text_Display>(pw).textcolor(pColour);
		reference_to<Fl_Text_Display>(pw).textfont(pFont);
	}

	// -----------------------------------------------------------------------------

	void MultilineScroll_Outbox::put(const string& s)
	{
		mTextBuffer->text(s.c_str());
	}

	// -----------------------------------------------------------------------------

	void MultilineScroll_Outbox::attach(Window& win)
	{
		pw = new Fl_Text_Display(loc.x, loc.y, width, height, label.c_str());
		reference_to<Fl_Text_Display>(pw).buffer(mTextBuffer);
		own = &win;
	}

	// -----------------------------------------------------------------------------

	int Menu::attach(Button& b)
	{
		b.width = width;
		b.height = height;

		switch (k) 
		{
		case horizontal:
			b.loc = Point(loc.x + offset, loc.y);
			offset += b.width;
			break;
		case vertical:
			b.loc = Point(loc.x, loc.y + offset);
			offset += b.height;
			break;
		}
		selection.push_back(&b);
		return int(selection.size() - 1);
	}

	//------------------------------------------------------------------------------

	int Menu::attach(Button* p)
	{
		//	owned.push_back(p);
		return attach(*p);
	}

	//------------------------------------------------------------------------------

	Lines_window::Lines_window(Point xy, int w, int h, const string& title)
		: Window{ xy, w, h, title.c_str() }
		, m_colourMenu	{ Point{double(x_max() - 70), 40}, 70, 20, Menu::vertical, "colour" }
		, m_menuButton	{ Point{double(x_max() - 80), 30}, 80, 20, "colour menu", cb_menu }
		, m_lsMenu		{ Point{double(x_max() - 70), 100}, 70, 20, Menu::vertical, "line style" }
		, m_lsButton	{ Point{double(x_max() - 100), 100}, 100, 20, "line style menu", cb_lsMenu }
		, m_nextButton	{ Point{double(x_max() - 150), 0}, 70, 20, "Next Point",
						[](Address, Address pw) {reference_to<Lines_window>(pw).next(); } }
		, m_quitButton	{ Point{double(x_max() -  70), 0}, 70, 20, "Quit",
						[](Address, Address pw) {reference_to<Lines_window>(pw).quit(); } }
		, m_nextX		{ Point{double(x_max() - 310), 0}, 50, 20, "next x:" }
		, m_nextY		{ Point{double(x_max() - 210), 0}, 50, 20, "next y:" }
		, m_xyOut		{ Point{100,0}, 100, 20, "current (x,y):" }
	{
		attach(m_nextButton);
		attach(m_quitButton);
		attach(m_nextX);
		attach(m_nextY);
		attach(m_xyOut);
		attach(m_lines);

		m_colourMenu.attach(new Button{ Point(0,0), 0, 0, "red", cb_red });
		m_colourMenu.attach(new Button{ Point(0,0), 0, 0, "blue", cb_blue });
		m_colourMenu.attach(new Button{ Point(0,0), 0, 0, "black", cb_black });
		attach(m_colourMenu);

		m_colourMenu.hide();
		attach(m_menuButton);

		m_lsMenu.attach(new Button{ Point(0,0), 0, 0, "solid",
			[](Address, Address addr) {reference_to<Lines_window>(addr).changeStyle(Line_style::solid); } 
			});
		m_lsMenu.attach(new Button{ Point(0,0), 0, 0, "dash",
			[](Address, Address addr) {reference_to<Lines_window>(addr).changeStyle(Line_style::dash); }
			});
		m_lsMenu.attach(new Button{ Point(0,0), 0, 0, "dot",
			[](Address, Address addr) {reference_to<Lines_window>(addr).changeStyle(Line_style::dot); }
			});
		m_lsMenu.attach(new Button{ Point(0,0), 0, 0, "dashdot",
			[](Address, Address addr) {reference_to<Lines_window>(addr).changeStyle(Line_style::dashdot); }
			});
		m_lsMenu.attach(new Button{ Point(0,0), 0, 0, "dashdotdot",
			[](Address, Address addr) {reference_to<Lines_window>(addr).changeStyle(Line_style::dashdotdot); }
			});
		attach(m_lsMenu);

		m_lsMenu.hide();
		attach(m_lsButton);
	}

	// -----------------------------------------------------------------------------

	void Lines_window::next()
	{
		double x = m_nextX.get_int();
		double y = m_nextY.get_int();
		m_lines.add(Point{ x,y });

		//update current position readout
		ostringstream ss;
		ss << '(' << x << ',' << y << ')';
		m_xyOut.put(ss.str());

		redraw();
	}

	// -----------------------------------------------------------------------------

	void Lines_window::quit()
	{
		hide();		// fltk idiom to delete window
	}

	// -----------------------------------------------------------------------------

} // namespace Graph_lib

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


