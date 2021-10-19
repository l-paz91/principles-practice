// -----------------------------------------------------------------------------
//
// This is a GUI support code to the chapters 12-16 of the book
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#ifndef GUI_GUARD
#define GUI_GUARD

#include "Window.h"
#include "Graph.h"

#include <Fl/Fl_Text_Display.H>

// -----------------------------------------------------------------------------

namespace Graph_lib 
{
	//------------------------------------------------------------------------------

	typedef void* Address;    // Address is a synonym for void*
	typedef void(*Callback)(Address, Address);    // FLTK's required function type for all callbacks

	//------------------------------------------------------------------------------

	template<class W> W& reference_to(Address pw)
		// treat an address as a reference to a W
	{
		return *static_cast<W*>(pw);
	}

	//------------------------------------------------------------------------------

	class Widget 
	{
		// Widget is a handle to an Fl_widget - it is *not* an Fl_widget
		// We try to keep our interface classes at arm's length from FLTK
	public:
		Widget(Point xy, int w, int h, const string& s, Callback cb)
			: loc(xy), width(w), height(h), label(s), do_it(cb)
		{}

		virtual void move(int dx, int dy) { hide(); pw->position(int(loc.x = dx), int(loc.y = dy)); show(); }
		virtual void hide() { pw->hide(); }
		virtual void show() { pw->show(); }
		virtual void attach(Window&) = 0;

		Point loc;
		int width;
		int height;
		string label;
		Callback do_it;

		virtual ~Widget() {}

	protected:
		Window* own;    // every Widget belongs to a Window
		Fl_Widget* pw;  // connection to the FLTK Widget
	private:
		Widget& operator=(const Widget&); // don't copy Widgets
		Widget(const Widget&);
	};

	//------------------------------------------------------------------------------

	struct FakeBkg : Widget
	{
		FakeBkg(Point xy, int w, int h, const char* filename)
			: Widget(xy, w, h, "", 0)
			, m_image(new Fl_JPEG_Image(filename))
		{}

		void attach(Window& win);

	private:
		Fl_Image* m_image;
	};

	// -----------------------------------------------------------------------------

	struct Button : Widget 
	{
		Button(Point xy, int w, int h, const char* label, Callback cb)
			: Widget(xy, w, h, label, cb)
		{}

		void setColor(Color::Color_type c) { pw->color(c); }

		void attach(Window&);
	};

	//------------------------------------------------------------------------------

	struct In_box : Widget 
	{
		In_box(Point xy, int w, int h, const string& s)
			:Widget(xy, w, h, s, 0) 
		{ }

		int get_int();
		float get_float();
		string get_string();

		void put(const string& s);	// for displaying before doing operations on input

		void attach(Window& win);
	};

	//------------------------------------------------------------------------------

	struct Out_box : Widget 
	{
		Out_box(Point xy, int w, int h, const string& s)
			:Widget(xy, w, h, s, 0) 
		{ }

		void put(int);
		void put(const string&);

		void attach(Window& win);
	};

	// -----------------------------------------------------------------------------

	struct Multiline_Outbox : Widget
	{
		Multiline_Outbox(Point xy, int w, int h, const string& s)
			:Widget(xy, w, h, s, 0) 
		{ }

		void setSizeColourFont(int pSize = 16, Fl_Color pColour = Color::black, Fl_Font pFont = Font::screen);

		void put(const string&);
		void attach(Window& win);
	};

	//------------------------------------------------------------------------------

	struct MultilineScroll_Outbox : Widget
	{
		MultilineScroll_Outbox(Point xy, int w, int h, const string& s)
			: Widget(xy, w, h, s, 0)
			, mTextBuffer( new Fl_Text_Buffer() )
		{ }

		void setSizeColourFont(int pSize = 16, Fl_Color pColour = Color::black, Fl_Font pFont = Font::screen);

		void put(const string&);
		void attach(Window& win);

		Fl_Text_Buffer* mTextBuffer;
	};


	// -----------------------------------------------------------------------------

	struct Menu : Widget 
	{
		enum Kind { horizontal, vertical };

		Menu(Point xy, int w, int h, Kind kk, const string& label)
			: Widget(xy, w, h, label, 0)
			, k(kk)
			, offset(0)
		{}

		Vector_ref<Button> selection;
		Kind k;
		int offset;
		int attach(Button& b);      // Menu does not delete &b
		int attach(Button* p);      // Menu deletes p

		void show()                 // show all buttons
		{			
			for (int i = 0; i < selection.size(); ++i)
				selection[i].show();
		}
		void hide()                 // hide all buttons
		{
			for (int i = 0; i < selection.size(); ++i)
				selection[i].hide();
		}
		void move(int dx, int dy)   // move all buttons
		{
			for (int i = 0; i < selection.size(); ++i)
				selection[i].move(dx, dy);
		}

		void attach(Window& win)    // attach all buttons
		{
			for (int i = 0; i < selection.size(); ++i) win.attach(selection[i]);
			own = &win;
		}

	};

	//------------------------------------------------------------------------------

	class Lines_window : public Window
	{
	public:
		Lines_window(Point xy, int w, int h, const string& title);
		Open_polyline m_lines;

		Menu m_colourMenu;
		Button m_menuButton;

		Menu m_lsMenu;
		Button m_lsButton;

		void change(Color c) { m_lines.set_color(c); hideMenu(); redraw(); }
		void hideMenu() { m_colourMenu.hide(); m_menuButton.show(); }
		void hideLSmenu() { m_lsMenu.hide(); m_lsButton.show(); }

		void redPressed() { change(Color::red); }
		void bluePressed() { change(Color::blue); }
		void blackPressed() { change(Color::black); }
		void menuPressed() { m_menuButton.hide(); m_colourMenu.show(); }
		void lsMenuPressed() { m_lsButton.hide(); m_lsMenu.show(); }
		void changeStyle(Line_style ls) { m_lines.set_style(ls); hideLSmenu(); redraw(); }

		//callback functions
		static void cb_red(Address, Address addr) { reference_to<Lines_window>(addr).redPressed(); }
		static void cb_blue(Address, Address addr) { reference_to<Lines_window>(addr).bluePressed(); }
		static void cb_black(Address, Address addr) { reference_to<Lines_window>(addr).blackPressed(); }
		static void cb_menu(Address, Address addr) { reference_to<Lines_window>(addr).menuPressed(); }
		static void cb_lsMenu(Address, Address addr) { reference_to<Lines_window>(addr).lsMenuPressed(); }

	private:
		void next();
		void quit();

		Button m_nextButton;	//add (nextX, nextY) to lines
		Button m_quitButton;
		In_box m_nextX;
		In_box m_nextY;
		Out_box m_xyOut;
	};

} // of namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // GUI_GUARD
