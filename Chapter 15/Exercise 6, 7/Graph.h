// -----------------------------------------------------------------------------
#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <functional>
#include "Point.h"
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

double getpi();
const double PI = getpi();

double getSqrt(double n);

// -----------------------------------------------------------------------------

namespace Graph_lib 
{
	// defense against ill-behaved Linux macros:
	#undef major
	#undef minor

	// -----------------------------------------------------------------------------

	struct Color 
	{
		enum Color_type 
		{
			red = FL_RED, blue = FL_BLUE, green = FL_GREEN,
			yellow = FL_YELLOW, white = FL_WHITE, black = FL_BLACK,
			magenta = FL_MAGENTA, cyan = FL_CYAN, dark_red = FL_DARK_RED,
			dark_green = FL_DARK_GREEN, dark_yellow = FL_DARK_YELLOW, dark_blue = FL_DARK_BLUE,
			dark_magenta = FL_DARK_MAGENTA, dark_cyan = FL_DARK_CYAN, pink = 252, cream = 215,
			lime = 71, coral = 130
		};
		enum Transparency { invisible = 0, visible = 255 };

		Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
		Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
		Color(int cc) :c(Fl_Color(cc)), v(visible) { }
		Color(Transparency vv) :c(Fl_Color()), v(vv) { }
		Color(uchar r, uchar g, uchar b) { fl_color(r, g, b); c = fl_color(); }

		int as_int() const { return c; }
		char visibility() const { return v; }
		void set_visibility(bool visible) { v = visible; }
	private:
		unsigned char v;	// 0 or 1 for now
		Fl_Color c;
	};

	// -----------------------------------------------------------------------------

	struct Line_style 
	{
		enum Line_style_type 
		{
			solid = FL_SOLID,				// -------
			dash = FL_DASH,				// - - - -
			dot = FL_DOT,					// ....... 
			dashdot = FL_DASHDOT,			// - . - . 
			dashdotdot = FL_DASHDOTDOT,	// -..-..
		};

		Line_style(Line_style_type ss) :s(ss), w(0) { }
		Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
		Line_style(int ss) :s(ss), w(0) { }

		int width() const { return w; }
		int style() const { return s; }
	private:
		int s;
		int w;
	};

	// -----------------------------------------------------------------------------

	class Font 
	{
	public:
		enum Font_type 
		{
			helvetica = FL_HELVETICA,
			helvetica_bold = FL_HELVETICA_BOLD,
			helvetica_italic = FL_HELVETICA_ITALIC,
			helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
			courier = FL_COURIER,
			courier_bold = FL_COURIER_BOLD,
			courier_italic = FL_COURIER_ITALIC,
			courier_bold_italic = FL_COURIER_BOLD_ITALIC,
			times = FL_TIMES,
			times_bold = FL_TIMES_BOLD,
			times_italic = FL_TIMES_ITALIC,
			times_bold_italic = FL_TIMES_BOLD_ITALIC,
			symbol = FL_SYMBOL,
			screen = FL_SCREEN,
			screen_bold = FL_SCREEN_BOLD,
			zapf_dingbats = FL_ZAPF_DINGBATS
		};

		Font(Font_type ff) :f(ff) { }
		Font(int ff) :f(ff) { }

		int as_int() const { return f; }
	private:
		int f;
	};

	// -----------------------------------------------------------------------------

	template<class T> class Vector_ref 
	{
		vector<T*> v;
		vector<T*> owned;
	public:
		Vector_ref() {}

		Vector_ref(T* a, T* b = 0, T* c = 0, T* d = 0)
		{
			if (a) push_back(a);
			if (b) push_back(b);
			if (c) push_back(c);
			if (d) push_back(d);
		}

		~Vector_ref() { for (unsigned int i = 0; i < owned.size(); ++i) delete owned[i]; }

		void push_back(T& s) { v.push_back(&s); }
		void push_back(T* p) { v.push_back(p); owned.push_back(p); }

		// ???void erase(???)

		T& operator[](int i) { return *v[i]; }
		const T& operator[](int i) const { return *v[i]; }
		int size() const { return v.size(); }
	};

	typedef double Fct(double);

	// -----------------------------------------------------------------------------

	// deals with color and style, and holds sequence of lines
	class Shape 
	{		
	protected:
		Shape() { set_color(Color::black); }

		// add() the Points to this Shape
		Shape(initializer_list<Point> p)
			: points(p)
		{}

		void add(Point p) { points.push_back(p); }
		
	public:
		void draw() const;					// deal with color and draw_lines
	protected:
		virtual void draw_lines() const;	// simply draw the appropriate lines
	public:
		virtual void move(int dx, int dy);	// move the shape +=dx and +=dy
		void set_point(int i, Point p) { points[i] = p; }
		void set_color(Color col) { lcolor = col; }
		Color color() const { return lcolor; }
		void setLineVisibility(bool visbility) { lcolor.set_visibility(visbility); }

		void set_style(Line_style sty) { ls = sty; }
		Line_style style() const { return ls; }

		void setFillVisibility(bool visibility) { fcolor.set_visibility(visibility); }
		void set_fill_color(Color col) { fcolor = col; }
		Color fill_color() const { return fcolor; }

		Point point(int i) const { return points[i]; }
		int number_of_points() const { return int(points.size()); }
		//clears all the points in a shape
		void resetPoints() { points.clear(); }

		enum Directions {
			N, S, E, W, CENTER, NE, SE, SW, NW
		};
		virtual Point getPointDirection(Directions d);

		virtual ~Shape() { }
		/*
		struct Window* attached;
		Shape(const Shape& a)
			:attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
		{
			if (a.attached)error("attempt to copy attached shape");
		}
		*/
		//Shape(const Shape&) = delete;
		//Shape& operator=(const Shape&) = delete;
	private:
		vector<Point> points;	// not used by all shapes
		Color lcolor{ fl_color() };
		Line_style ls{ 0 };
		Color fcolor{ Color::invisible };

		//	Shape(const Shape&);
		//	Shape& operator=(const Shape&);
	};

	// -----------------------------------------------------------------------------
	
	struct Function : Shape 
	{
		// the function parameters are not stored
		Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
		Function(std::function<double(double)>f , double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
		//Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);	
	};

	// -----------------------------------------------------------------------------

	struct StoredFct : Function
	{
	public:
		StoredFct(std::function<double(double)>f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25) 
			: Function(f,r1,r2, orig, count, xscale, yscale)
			, m_function(f)
			, m_minRange(r1)
			, m_maxRange(r2)
			, m_origin(orig)
			, m_axisLength(count)
			, m_xscale(xscale)
			, m_yscale(yscale)
		{}

		// resets all stored values
		void init(std::function<double(double)>f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);

	private:
		std::function<double(double)> m_function;
		Point m_origin;
		double m_minRange, m_maxRange;
		double m_xscale, m_yscale;
		int m_axisLength;
	};

	// -----------------------------------------------------------------------------

	struct Fill 
	{
		Fill() :no_fill(true), fcolor(0) { }
		Fill(Color c) :no_fill(false), fcolor(c) { }

		void set_fill_color(Color col) { fcolor = col; }
		Color fill_color() { return fcolor; }
	protected:
		bool no_fill;
		Color fcolor;
	};

	// -----------------------------------------------------------------------------

	struct Line : Shape 
	{
		Line(Point p1, Point p2) { add(p1); add(p2); }
	};

	// -----------------------------------------------------------------------------

	struct Rectangle : Shape 
	{
		Rectangle(Point xy, double ww, double hh) :w{ ww }, h{ hh }
		{
			if (h <= 0 || w <= 0) error("Bad rectangle: non-positive side");
			add(xy);
		}
		Rectangle(Point x, Point y) :w{ y.x - x.x }, h{ y.y - x.y }
		{
			if (h <= 0 || w <= 0) error("Bad rectangle: first point is not top left");
			add(x);
		}

		void draw_lines() const;

		Point getPointDirection(Directions d);

		double height() const { return h; }
		double width() const { return w; }
	private:
		double h;			// height
		double w;			// width
	//	Color fcolor;	// fill color; 0 means "no fill"
	};

	// -----------------------------------------------------------------------------

	struct Striped_rectangle : Rectangle
	{
		Striped_rectangle(Point xy, double width, double height, int stripeW = 1, Color c = Color::black)
			: Rectangle(xy, width, height)
			, m_stripeWidth(stripeW)
			, m_stripeCol(c)
		{
			validateRect();
			set_fill_color(m_stripeCol);
		}

		Striped_rectangle(Point x, Point y, int stripeW = 1, Color c = Color::black)
			: Rectangle(x, y)
			, m_stripeWidth(stripeW)
			, m_stripeCol(c)
		{
			validateRect();
			set_fill_color(m_stripeCol);
		}

		void draw_lines() const;

	private:
		void validateRect();
		Color m_stripeCol;
		int m_stripeWidth;
	};

	// -----------------------------------------------------------------------------

	pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel);
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection);

	// -----------------------------------------------------------------------------

	struct Open_polyline : Shape 
	{	// open sequence of lines
		using Shape::Shape;
		Open_polyline() {}
		Open_polyline(initializer_list<Point> p)
			: Shape(p)
		{}

		void add(Point p) { Shape::add(p); }
		void draw_lines() const;
	};

	// -----------------------------------------------------------------------------

	struct Closed_polyline : Open_polyline 
	{	// closed sequence of lines
		using Open_polyline::Open_polyline;
		Closed_polyline() {}

		Closed_polyline(initializer_list<Point> p)
			: Open_polyline(p)
		{}

		void draw_lines() const;

		//	void add(Point p) { Shape::add(p); }
	};

	// -----------------------------------------------------------------------------

	struct Striped_closed_polyline : Closed_polyline
	{
		using Closed_polyline::Closed_polyline;
		//Striped_closed_polyline(int stripeW = 1, Color c = Color::dark_magenta)
		//	: m_stripeCol(c)
		//	, m_stripeWidth(stripeW)
		//{
		//	set_fill_color(m_stripeCol);
		//}
		//Striped_closed_polyline() {}

		Striped_closed_polyline(initializer_list<Point> p)
			: Closed_polyline(p)
		{
			m_stripeWidth = 1;
			add(Point{ point(0).x, point(0).y }); //close shape & prevent intersection shenanigans
		}

		void setStripeWidth(int width) { m_stripeWidth = width; }

		void draw_lines() const;

	private:
		//void validateRect();
		int m_stripeWidth;
	};

	// -----------------------------------------------------------------------------

	struct Polygon : Closed_polyline 
	{	// closed sequence of non-intersecting lines
		using Closed_polyline::Closed_polyline;
		Polygon() {}
		void add(Point p);
		void draw_lines() const;
	};

	// -----------------------------------------------------------------------------

	//open sequence of lines, first and last point must meet up
	//supports any type of polygon i.e complex, convex, regular/irregular
	//however, it only errors if less than 3 points are supplied or the points don't
	//meet up
	struct Poly : Open_polyline
	{
		using Open_polyline::Open_polyline;
		Poly() {}
		Poly(initializer_list<Point> p)
			: Open_polyline(p)
		{
			validatePoly();
		}

		void draw_lines() const { Open_polyline::draw_lines(); }

	private:
		void validatePoly();
	};

	// -----------------------------------------------------------------------------

	// a Polygon whose sides must all be the same length
	struct Regular_polygon : Polygon
	{
		Regular_polygon(Point center, double radius, int numOfSides, double rotate = 0)
		{
			m_numSides = numOfSides;
			m_radius = radius;
			m_apothem = radius * cos(PI / numOfSides);
			m_sideLength = radius + radius * sin(PI / numOfSides);

			for (int i = 0; i < numOfSides; ++i)
			{
				double x = radius * cos(2 * PI * i / numOfSides + rotate) + center.x;
				double y = radius * sin(2 * PI * i / numOfSides + rotate) + center.y;
				Polygon::add(Point{ x, y });
			}
		}

		void draw_lines() const { Polygon::draw_lines(); }
	private:
		using Shape::set_point;
		using Shape::add;

		int m_numSides;
		double m_sideLength, m_radius, m_apothem;	
	};

	// -----------------------------------------------------------------------------

	struct Regular_Hexagon : Regular_polygon
	{
		Regular_Hexagon(Point center, double radius)
			: Regular_polygon(center, radius, 6)
		{}

		Regular_Hexagon(Point center, double radius, Graph_lib::Color fill, Graph_lib::Color outline = Color::black)
			: Regular_Hexagon(center, radius)
		{
			set_color(outline);
			set_fill_color(fill);
		}

		void draw_lines() const;		
		static void hexagonTile(vector<Regular_Hexagon>& v, int numHex, int radius, int widthTile, Point p);

	private:
		using Shape::set_point;
		using Shape::add;
	};

	// -----------------------------------------------------------------------------

	struct Regular_Octagon : Regular_polygon
	{
		Regular_Octagon(Point center, double radius)
			: Regular_polygon(center, radius, 8)
		{}

		Regular_Octagon(Point center, double radius, Graph_lib::Color fill, Graph_lib::Color outline = Color::black)
			: Regular_Octagon(center, radius)
		{
			set_color(outline);
			set_fill_color(fill);
		}

		void draw_lines() const;

	private:
		using Shape::set_point;
		using Shape::add;
	};

	// -----------------------------------------------------------------------------

	struct EquilateralTriangle : Regular_polygon
	{
		EquilateralTriangle(Point center, double radius)
			: Regular_polygon(center, radius, 3, 0.523599) //awful magic number...30 degrees
		{
			set_color(Color::black);
		}

		void draw_lines() const { Polygon::draw_lines(); }
	};

	// -----------------------------------------------------------------------------

	struct RightTriangle : Polygon
	{
		// p2 must be right-angle point (otherwise it may error)
		RightTriangle(Point p1, Point p2, Point p3)
		{
			Polygon::add(p1);
			Polygon::add(p2);
			Polygon::add(p3);
			validateTriangle(p1, p2, p3);
		}

		RightTriangle(Point p1, Point p2, Point p3, Graph_lib::Color fill, Graph_lib::Color outline = Color::magenta)
			: RightTriangle(p1, p2, p3)
		{
			set_color(outline);
			set_fill_color(fill);
		}

		void draw_lines() const { Polygon::draw_lines(); }

		static double findAngleBetween2Lines(Point beginLine1, Point endLine1, Point beginLine2, Point endLine2)
		{
			double angle1 = abs(atan2(beginLine1.y - endLine1.y, beginLine1.x - endLine1.x));
			double angle2 = abs(atan2(beginLine2.y - endLine2.y, beginLine2.x - endLine2.x));

			return abs(angle1 - angle2)*(180 / PI);
		}

		static void rightTriangleTileWindow(vector<RightTriangle>& v, int sideLength);

	private:
		void validateTriangle(Point p1, Point p2, Point p3);

		double a1, a2, a3;
	};

	// -----------------------------------------------------------------------------

	struct Star : Closed_polyline
	{
		Star(Point center, double outerRadius, double innerRadius, double startAngle = 0, int numOfPoints = 5);

		Point getPointOnStar(int angle, double radius);
		void add(Point p) { Closed_polyline::add(p); }
		void draw_lines() const { Closed_polyline::draw_lines(); }
	private:
		Point m_center;
		double m_radius;
	};

	// -----------------------------------------------------------------------------

	struct Box : Shape
	{	
		Box(Point p, int ww, int hh, int cornerRoundAmount)
			: w{ ww }
			, h{ hh }
			, round{ cornerRoundAmount }
		{
			if ((w - cornerRoundAmount < 0) || (h - cornerRoundAmount < 0))
				error("roundness cannot exceed given height/width");
			add(Point{ p.x, p.y});
		}

		void draw_lines() const;
		void change_roundAmount(int cornerRoundAmount)
		{ 
			if ((w - cornerRoundAmount < 0) || (h - cornerRoundAmount < 0))
				error("roundness cannot exceed given height/width");
			else
				round = cornerRoundAmount;
		}
		int getWidth() const { return w; };
		int getLength() const { return h; }

	private:
		int w, h;
		int round;
	};

	// -----------------------------------------------------------------------------

	struct Arrow : Shape
	{
		Arrow(Point from, Point to, int ArrowSize)
			: arrowSize(ArrowSize)
		{
			add(from);
			add(to);
		}

		void draw_lines() const;
		void moveArrow(Point from, Point to) { set_point(0, from); set_point(1, to); }
		void changeArrowSize(int ArrowSize) { arrowSize = ArrowSize; }

	private:
		int arrowSize;
	};

	// -----------------------------------------------------------------------------

	struct Lines : Shape 
	{	// independent lines
		Lines() {}

		Lines(initializer_list<Point> lst) 
			: Shape{ lst } 
		{ 
			if (lst.size() % 2) 
				error("odd number of points for Lines"); 
		}

		void draw_lines() const;
		void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
	};

	// -----------------------------------------------------------------------------

	struct Text : Shape 
	{
		// the point is the bottom left of the first letter
		Text() {}	//default constructor
		Text(Point x, const string& s) : lab{ s } 
		{ 
			//initialise the font face
			set_font(Font::helvetica);
			set_font_size(14); //14 is default FLTK size
			fl_font(fnt.as_int(), fnt_sz);
			add(x);
		}

		void draw_lines() const;

		void set_label(const string& s) { lab = s; }
		string label() const { return lab; }

		void set_font(Font f) { fnt = f; }
		Font font() const { return Font(fnt); }

		void set_font_size(int s) { fnt_sz = s; }
		int font_size() const { return fnt_sz; }

		//length of text message
		double length() { return fl_width(lab.c_str()); }
		
	private:
		string lab;	// label
		Font fnt{ fl_font() };
		int fnt_sz{ (14 < fl_size()) ? fl_size() : 14 };	// at least 14 point
	};

	// -----------------------------------------------------------------------------

	struct TextBox : Text
	{
		TextBox(Point p, string msg, int cornerRoundAmount )
			: Text(Point(p.x + 10, p.y + 20), msg)
			, box(p, length() + 20, font_size() + 20, cornerRoundAmount)
		{}

		void setColours(Color boxOutline, Color boxFill, Color textColor);
		void draw_lines() const;

		Point getTopCenter()    const { return Point{ box.point(0).x + box.getWidth()*0.5, box.point(0).y }; }
		Point getBottomCenter() const { return Point{ box.point(0).x + box.getWidth()*0.5 , box.point(0).y + box.getLength()}; }
		Point getLeftCenter()   const { return Point{ box.point(0).x, box.point(0).y + (box.getLength()*0.5) }; }
		Point getRightCenter()  const { return Point{ box.point(0).x + box.getWidth(), box.point(0).y + (box.getLength()*0.5) }; }

		int getW() const { return box.getWidth(); }
		int getH() const { return box.getLength(); }

		Box box;
	private:	
		string message;
	};

	// -----------------------------------------------------------------------------

	struct Axis : Shape 
	{
	public:
		// representation left public
		enum Orientation { x, y, z };
		Axis(Orientation d, Point xy, int length, int nummber_of_notches = 0, string label = "");

		void draw_lines() const;
		void move(int dx, int dy);
		void setLabel(string s) { label.set_label(s); }
		void set_color(Color c);

	private:
		Point m_xy;
		Text label;
		Lines notches;
		int m_numNotches;

	};

	// -----------------------------------------------------------------------------

	struct Circle : Shape 
	{
		Circle(Point p, int rr)	// center and radius
			:r{ rr } 
			, diameter(rr*2)
		{
			add(Point{ p.x - r, p.y - r});
		}

		void draw_lines() const;

		Point center() const { return { point(0).x + r, point(0).y + r }; }
		Point getPointOnCircle(double angle) const;

		Point getPointDirection(Directions d);

		void set_radius(int rr) { r = rr; }
		int radius() const { return r; }
		int diam() const { return diameter; }
	private:
		int r;
		int diameter;
	};

	// -----------------------------------------------------------------------------

	struct Immobile_circle : Circle
	{
		Immobile_circle(Point p, int radius)
			: Circle(p, radius)
		{}

	private:
		using Circle::set_point;
		using Circle::move;
	};

	// -----------------------------------------------------------------------------

	struct Striped_circle : Circle
	{
		Striped_circle(Point p, int radius, int stripeW = 1, Color stripeC = Color::black)
			: Circle(p, radius)
			, m_stripeCol(stripeC)
			, m_stripeWidth(stripeW)
		{
			validateCircle();
			set_fill_color(m_stripeCol);
		}

		void draw_lines() const;

	private:
		void validateCircle();
		Color m_stripeCol;
		int m_stripeWidth;
	};

	// -----------------------------------------------------------------------------

	struct Smiley : Circle
	{
		Smiley(Point p, int radius)
			: Circle(p, radius)
		{}

		void draw_lines() const;
	};

	// -----------------------------------------------------------------------------

	struct SmileyHat : Smiley
	{
		SmileyHat(Point p, int radius)
			: Smiley(p, radius)
		{
			initHat();
		}

		~SmileyHat() { delete p; }

		void draw_lines() const;
	private:
		void initHat();
		Fl_Image* p;
	};

	// -----------------------------------------------------------------------------

	struct Frowny : Circle
	{
		Frowny(Point p, int radius)
			: Circle(p, radius)
		{}

		void draw_lines() const;
	};

	// -----------------------------------------------------------------------------

	struct FrownyHat : Frowny
	{
		FrownyHat(Point p, int radius)
			: Frowny(p, radius)
		{
			initHat();
		}

		~FrownyHat() { delete p; }

		void draw_lines() const;
	private:
		void initHat();
		Fl_Image* p;
	};



	// -----------------------------------------------------------------------------

	struct Ellipse : Shape 
	{
		Ellipse(Point p, int ww, int hh)	// center, min, and max distance from center
			:w{ ww }, h{ hh } {
			add(Point{ p.x - ww, p.y - hh });
		}

		void draw_lines() const;
		Point getPointOnEllipse(int angle);
		Point getPointDirection(Directions d);

		Point center() const { return{ point(0).x + w, point(0).y + h }; }
		Point focus1() const { return{ center().x + int(sqrt(double(w*w - h * h))), center().y }; }
		Point focus2() const { return{ center().x - int(sqrt(double(w*w - h * h))), center().y }; }

		void set_major(int ww) { w = ww; }
		int major() const { return w; }
		void set_minor(int hh) { h = hh; }
		int minor() const { return h; }
	private:
		int w;
		int h;
	};
	/*
	struct Mark : Text {
		static const int dw = 4;
		static const int dh = 4;
		Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
	};
	*/

	// -----------------------------------------------------------------------------

	struct Arc : Shape
	{
		//angle1 must be less than or equal to angle2
		Arc(Point p, int ww, int hh, int a1, int a2)
			: w{ ww }, h{ hh }, angle1{ a1 }, angle2{ a2 }
		{
			add(Point{ p.x, p.y });
		}

		void draw_lines() const;
		void change_angle(int a1, int a2);

	private:
		int w, h;
		int angle1, angle2;
	};

	// -----------------------------------------------------------------------------

	struct Marked_polyline : Open_polyline 
	{
		Marked_polyline(const string& m) : mark(m) { }
		void draw_lines() const;
	private:
		string mark;
	};

	// -----------------------------------------------------------------------------

	struct Marks : Marked_polyline 
	{
		Marks(const string& m) :Marked_polyline(m)
		{
			set_color(Color(Color::invisible));
		}
	};

	// -----------------------------------------------------------------------------

	//struct Mark : Marks 
	//{
	//	Mark(Point xy, char c) : Marks(string(1, c)) { add(xy); }
	//};

	// -----------------------------------------------------------------------------

	struct Mark : Shape 
	{
		Mark(Point p, char m, Graph_lib::Color c)
			: mark(string(1, m))
		{
			add(p);
			set_color(c);
		}

		Mark(char m) : 
			mark(string(1,m)) 
		{ }

		void add(Point p) { Shape::add(p); }
		void set_point(int i, Point p) { Shape::set_point(i, p); }
		void draw_lines() const;

	private:
		string mark;
	};
	
	// -----------------------------------------------------------------------------

	struct Bad_image : Fl_Image 
	{
		Bad_image(int h, int w) : Fl_Image(h, w, 0) { }
		void draw(int x, int y, int, int, int, int) { draw_empty(x, y); }
	};

	// -----------------------------------------------------------------------------

	struct Suffix 
	{
		enum Encoding { none, jpg, gif, bmp, png };
	};

	Suffix::Encoding get_encoding(const string& s);

	// -----------------------------------------------------------------------------

	struct Image : Shape 
	{
		Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
		~Image() { delete p; }
		void draw_lines() const;
		void set_mask(Point xy, int ww, int hh) { w = ww; h = hh; cx = xy.x; cy = xy.y; }
		void move(double dx, double dy) { Shape::move(dx, dy); p->draw(point(0).x, point(0).y); }
		void changePoint(double x, double y) { Shape::set_point(0, Point{ x, y }); }
	private:
		int w, h, cx, cy; // define "masking box" within image relative to position (cx,cy)
		Fl_Image* p;
		Text fn;
	};

	// -----------------------------------------------------------------------------

	//helper function for sorting vectors of Points
	bool compareByX(const Point& a, const Point& b);
	bool compareByY(const Point& a, const Point& b);

	// -----------------------------------------------------------------------------

	struct Group : Shape
	{
		Group();
		~Group()
		{
			delete m_light;
			delete m_dark;
			delete m_board;
		}

		enum MoveDir {
			NorthEast, SouthEast, SouthWest, NorthWest
		};

		void draw_lines() const;
		void moveLightPiece(MoveDir direction, int pieceNum);
		void moveDarkPiece(MoveDir direction, int pieceNum);
		void removePiece(int pieceNum);
	private:
		using Shape::move;

		Fl_Image* m_light;
		Fl_Image* m_dark;
		Fl_Image* m_board;
		vector<Rectangle> v_light;
		vector<Rectangle> v_dark;
	};

	// -----------------------------------------------------------------------------

	struct Pseudo_window : Shape
	{
		Pseudo_window(string l)
			: m_window(Point{200,200}, "window.png")
			, m_window2(Point{100, 100}, "window1.png")
			, m_clip(Point{600, 550}, "clipp.png")
			, label(Point{130, 118}, l)
		{
			label.set_font_size(14);
			label.set_color(Color::white);
		}

		void draw_lines() const;

	private:
		Image m_window;
		Image m_window2;
		Image m_clip;
		Text label;
	};

	// -----------------------------------------------------------------------------

	struct Binary_tree : Shape
	{
		enum NodeType {
			NODE_circle, NODE_triangle, NODE_square
		};

		Binary_tree(int levels, int y, NodeType nodeType = NODE_triangle, int treeSize = 1)
			: m_levels(levels)
			, m_offset(y)
			, m_treeSize(treeSize)
			, m_arrowColour(Color::black)
			, m_arrowDirection(0)
			, m_useArrowLine(false)
			, m_nodeType(nodeType)
		{
			if (treeSize <= 0)
				error("Tree size cannot be less than or equal to 0");
			initNodes();
		}

		void draw_lines() const;
		void setLineAsArrow(bool direction, Color col);
		void addTextToNode(int node, string text);

	private:
		struct NodeText {
			NodeText(int n, string s) : node(n), text(s) {}
			int node;
			string text;
		};

		void initNodes();

		vector<Circle> v_nodes;
		vector<NodeText> v_nodeText;
		vector<Line> v_lines;
		vector<int> v_numOnEachLine;

		Color m_arrowColour;
		int m_levels, m_offset, m_treeSize;
		bool m_arrowDirection, m_useArrowLine;
		NodeType m_nodeType;
	};

	// -----------------------------------------------------------------------------

	struct CustomBinaryTree : Shape
	{
		CustomBinaryTree(string rootNode)
		{
			mV_CBTEntries.push_back(CBTentry(rootNode, rootNode, Color::green, 20));
		}

		void addEntry(string label, string parentName, Color color, int indentAmount);

		void draw_lines() const;

	private:	
		//disgustingly hacky but I don't care anymore
		struct CBTentry {
			CBTentry(string l, string p, Color color, int indentAmount) 
				: label(l), parent(p), boxColour(color), indentX(indentAmount) {}
			string label;
			string parent;
			Color boxColour;
			int indentX;
		};

		vector<CBTentry> mV_CBTEntries;
	};
	
	// -----------------------------------------------------------------------------
	class Simple_window;	//forward declare (as definition is in cpp)

	class Controller
	{
	public:	
		Controller()
			: m_level(0)
			, m_isClassOn(false)
		{}

		virtual void on() { m_isClassOn = true; }
		virtual void off() { m_isClassOn = false; }
		virtual void set_level(int i) { m_level = i; }
		virtual Text show() { return Text(); }

	protected:
		int m_level;
		bool m_isClassOn;
	};

	// -----------------------------------------------------------------------------

	class Test_Controller : public Controller
	{
	public:
		Test_Controller() {}

		Text show() override;
	};

	// -----------------------------------------------------------------------------

	class Line_Controller : public Controller
	{
	public:
		Line_Controller(Shape* shape) 
			: m_shapePtr(shape)
		{}

		virtual void set_level(int i) override
		{
			m_shapePtr->set_color(Color(i));
		}
	protected:
		Shape* m_shapePtr;
	};

	// -----------------------------------------------------------------------------

	class Move_Controller : public Line_Controller
	{
	public:
		Move_Controller(Shape* shape)
			: Line_Controller(shape)
		{}

		void set_level(int i) override
		{
			m_shapePtr->move(i, i);
		}
	};

	// -----------------------------------------------------------------------------

	struct BarChart : Shape
	{
	public:
		BarChart(Simple_window* win, vector<double>& heightValues);

		void setTitle(string s) { m_title.set_label(s); }
		void labelBars(bool b) { m_showBarLabels = b; }
		void labelAxes(string xTitle, string yTitle) { m_x.setLabel(xTitle); m_y.setLabel(yTitle); }
		void fillBars(bool b) { m_fillBars = b; }
		void draw_lines() const;

	private:
		vector<double> mv_heightValues;
		Axis m_x, m_y;
		Text m_title;
		int m_barWidth;
		bool m_showBarLabels, m_fillBars;
	};

	// -----------------------------------------------------------------------------

} //namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif
