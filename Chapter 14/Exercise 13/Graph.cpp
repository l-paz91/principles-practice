//------------------------------------------------------------------------------
#include "Graph.h"
#include "Window.h"
#include <map>
#include <cmath>

// -----------------------------------------------------------------------------

double getpi()
{
	double pi;
	__asm
	{
		fldpi
		fstp pi
	}
	return pi;
}

// -----------------------------------------------------------------------------

double getSqrt(double n)
{
	__asm
	{
		FLD n
		FSQRT
	}
}

//------------------------------------------------------------------------------

namespace Graph_lib
{
	void Shape::draw_lines() const
	{
		if (color().visibility() && 1 < points.size())	// draw sole pixel?
			for (unsigned int i = 1; i < points.size(); ++i)
				fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
	}

	//------------------------------------------------------------------------------

	void Shape::draw() const
	{
		Fl_Color oldc = fl_color();
		// there is no good portable way of retrieving the current style
		fl_color(lcolor.as_int());
		fl_line_style(ls.style(), ls.width());
		draw_lines();
		fl_color(oldc);	// reset color (to pevious) and style (to default)
		fl_line_style(0);
	}

	//------------------------------------------------------------------------------

	// does two lines (p1,p2) and (p3,p4) intersect?
	// if se return the distance of the intersect point as distances from p1
	inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
	{
		double x1 = p1.x;
		double x2 = p2.x;
		double x3 = p3.x;
		double x4 = p4.x;
		double y1 = p1.y;
		double y2 = p2.y;
		double y3 = p3.y;
		double y4 = p4.y;

		double denom = ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
		if (denom == 0) {
			parallel = true;
			return pair<double, double>(0, 0);
		}
		parallel = false;
		return pair<double, double>(((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / denom,
			((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / denom);
	}

	//------------------------------------------------------------------------------

	//intersection between two line segments
	//Returns true if the two segments intersect,
	//in which case intersection is set to the point of intersection
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection)
	{
		bool parallel;
		pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);
		if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
		intersection.x = p1.x + static_cast<int>(u.first*(p2.x - p1.x));
		intersection.y = p1.y + static_cast<int>(u.first*(p2.y - p1.y));

		return true;
	}

	//------------------------------------------------------------------------------

	void Polygon::add(Point p)
	{
		int np = number_of_points();

		if (1 < np) {	// check that thenew line isn't parallel to the previous one
			if (p == point(np - 1)) error("polygon point equal to previous point");
			bool parallel;
			line_intersect(point(np - 1), p, point(np - 2), point(np - 1), parallel);
			if (parallel)
				error("two polygon points lie in a straight line");
		}

		for (int i = 1; i < np - 1; ++i) {	// check that new segment doesn't interset and old point
			Point ignore(0, 0);
			if (line_segment_intersect(point(np - 1), p, point(i - 1), point(i), ignore))
				error("intersect in polygon");
		}


		Closed_polyline::add(p);
	}

	//------------------------------------------------------------------------------

	void Polygon::draw_lines() const
	{
		if (number_of_points() < 3) error("less than 3 points in a Polygon");
		Closed_polyline::draw_lines();
	}

	//------------------------------------------------------------------------------

	void Open_polyline::draw_lines() const
	{
		if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int i = 0; i < number_of_points(); ++i)
			{
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
			Shape::draw_lines();
	}

	//------------------------------------------------------------------------------

	void Closed_polyline::draw_lines() const
	{
		Open_polyline::draw_lines();

		if (color().visibility())	// draw closing line:
			fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
	}

	// -----------------------------------------------------------------------------

	void Striped_closed_polyline::draw_lines() const
	{
		//determine a bounding box for the polygon (this gives us the stripes)
		double xMin = point(0).x; double yMin = point(0).y;
		double xMax = point(0).x;  double yMax = point(0).y;
		for (int i = 0; i < number_of_points(); ++i)
		{
			if (point(i).x < xMin)
				xMin = point(i).x;
			if (point(i).x > xMax)
				xMax = point(i).x;
			if (point(i).y < yMin)
				yMin = point(i).y;
			if (point(i).y > yMax)
				yMax = point(i).y;
		}
		const int width = xMax - xMin;
		const int height = yMax - yMin;

		const int numOfLines = (width / m_stripeWidth) / 2;
		double x = xMin;
		double y = yMin;
		Point intersect;
		vector<Point> in;
		int intersectCount = 0;
		for (int i = 0; i < numOfLines; ++i)
		{
			//does the stripe hit one of the lines?
			for (int n = 0; n < number_of_points() - 1; ++n)
			{
				if (line_segment_intersect(Point{ x, y }, Point{ x, y + height },
					Point{ point(n).x, point(n).y }, Point{ point(n + 1).x, point(n + 1).y }, intersect))
				{
					if (intersectCount < 2)
					{
						in.push_back(intersect);
						++intersectCount;		//we only want to pushback 2 intersects for any given line
					}
				}
			}
			x += 2;	//skip to the next line
			intersectCount = 0;
		}

		//match up the intersects
		fl_color(fill_color().as_int());
		for (int i = 0; i < in.size() - 1; i += 2)
			fl_line(in[i].x, in[i].y, in[i + 1].x, in[i + 1].y);

		//outline colour
		if (color().visibility())
			Shape::draw_lines();
	}

	//------------------------------------------------------------------------------

	void Poly::validatePoly()
	{
		//needs to have at least 3 points
		//first and last points should be the same
		if (number_of_points() < 3)
			error("Polygon needs at least 3 points");
		if (point(0) != point(number_of_points() - 1))
			error("First and last point of Polygon need to meet up");
	}

	// -----------------------------------------------------------------------------

	void Shape::move(int dx, int dy)
	{
		for (unsigned int i = 0; i < points.size(); ++i)
		{
			points[i].x += dx;
			points[i].y += dy;
		}
	}

	// -----------------------------------------------------------------------------

	Point Shape::getPointDirection(Directions d)
	{
		switch (points.size())
		{
		case 0:
			error("This shape has no points");
			break;
		case 1:
			return points[0];
		default:
			error("If the shape has more than 1 point, it should override this function with it's own code.");
			break;
		}
	}

	//------------------------------------------------------------------------------

	void Lines::draw_lines() const
	{
		//	if (number_of_points()%2==1) error("odd number of points in set of lines");
		if (color().visibility())
			for (int i = 1; i < number_of_points(); i += 2)
				fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
	}

	//------------------------------------------------------------------------------

	void Text::draw_lines() const
	{
		int ofnt = fl_font();
		int osz = fl_size();
		fl_font(fnt.as_int(), fnt_sz);
		fl_draw(lab.c_str(), point(0).x, point(0).y);
		fl_font(ofnt, osz);
	}

	//------------------------------------------------------------------------------

	Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale)
		// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
		// x coordinates are scaled by xscale and y coordinates scaled by yscale
	{
		if (r2 - r1 <= 0) error("bad graphing range");
		if (count <= 0) error("non-positive graphing count");
		double dist = (r2 - r1) / count;
		double r = r1;
		for (int i = 0; i < count; ++i)
		{
			add(Point(xy.x + int(r*xscale), xy.y - int(f(r)*yscale)));
			r += dist;
		}
	}

	//------------------------------------------------------------------------------

	void Rectangle::draw_lines() const
	{
		if (fill_color().visibility())
		{	// fill
			fl_color(fill_color().as_int());
			fl_rectf(point(0).x, point(0).y, w, h);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, w, h);
		}
	}

	// -----------------------------------------------------------------------------

	void Striped_rectangle::validateRect()
	{
		if (m_stripeWidth > width())
			error("Stripe width cannot be more than width.");
		if (m_stripeWidth < 1)
			error("Stripe width must be at least 1 pixel wide.");
	}

	// -----------------------------------------------------------------------------

	void Striped_rectangle::draw_lines() const
	{
		//striped fill
		//how many lines can we have?
		const int numOfLines = (width() / m_stripeWidth) / 2;
		int x = point(0).x + m_stripeWidth;
		int y = point(0).y;
		for (int i = 0; i < numOfLines; ++i)
		{
			fl_color(fill_color().as_int());
			fl_line_style(Line_style::solid, m_stripeWidth);	//only set the line style for the fill
			fl_line(x, y, x, y + height());
			x += m_stripeWidth * 2;
		}

		//outline
		if (color().visibility())
		{	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x - 1, point(0).y, width() + 1, height() + 1);	//-+1 to make outline 1px outside bounding bpx
		}
	}

	// -----------------------------------------------------------------------------

	Point Rectangle::getPointDirection(Directions d)
	{
		switch (d)
		{
		case NW:
			return point(0);
		case N:
			return Point(point(0).x + (w / 2), point(0).y);
		case NE:
			return Point(point(0).x + w, point(0).y);
		case E:
			return Point(point(0).x + w, point(0).y + (h / 2));
		case SE:
			return Point(point(0).x + w, point(0).y + h);
		case S:
			return Point(point(0).x + (w / 2), point(0).y + h);
		case SW:
			return Point(point(0).x, point(0).y + h);
		case W:
			return Point(point(0).x, point(0).y + (h / 2));
		case CENTER:
			return Point(point(0).x + (w / 2), point(0).y + (h / 2));
		default:
			error("That's an odd direction");
			break;
		}
	}

	//------------------------------------------------------------------------------

	Axis::Axis(Orientation d, Point xy, int length, int n, string lab)
		:label(Point(0, 0), lab)
	{
		if (length < 0) error("bad axis length");
		switch (d)
		{
		case Axis::x:
		{	Shape::add(xy);	// axis line
		Shape::add(Point(xy.x + length, xy.y));	// axis line
		if (1 < n) {
			int dist = length / n;
			int x = xy.x + dist;
			for (int i = 0; i < n; ++i)
			{
				notches.add(Point(x, xy.y), Point(x, xy.y - 5));
				x += dist;
			}
		}
		// label under the line
		label.move(length / 3, xy.y + 20);
		break;
		}
		case Axis::y:
		{
			Shape::add(xy);	// a y-axis goes up
			Shape::add(Point(xy.x, xy.y - length));
			if (1 < n)
			{
				int dist = length / n;
				int y = xy.y - dist;
				for (int i = 0; i < n; ++i) {
					notches.add(Point(xy.x, y), Point(xy.x + 5, y));
					y -= dist;
				}
			}
			// label at top
			label.move(xy.x - 10, xy.y - length - 10);
			break;
		}
		case Axis::z:
			error("z axis not implemented");
		}
	}

	//------------------------------------------------------------------------------

	void Axis::draw_lines() const
	{
		Shape::draw_lines();	// the line
		notches.draw();	// the notches may have a different color from the line
		label.draw();	// the label may have a different color from the line
	}

	//------------------------------------------------------------------------------

	void Axis::set_color(Color c)
	{
		Shape::set_color(c);
		notches.set_color(c);
		label.set_color(c);
	}

	//------------------------------------------------------------------------------

	void Axis::move(int dx, int dy)
	{
		Shape::move(dx, dy);
		notches.move(dx, dy);
		label.move(dx, dy);
	}

	//------------------------------------------------------------------------------

	void Circle::draw_lines() const
	{
		if (fill_color().visibility())
		{	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
	}

	// -----------------------------------------------------------------------------

	Point Circle::getPointOnCircle(double angle) const
	{
		Point p;
		double rad = angle * (PI / 180.0f);
		p.x = r * cos(rad) + center().x;
		p.y = r * sin(rad) + center().y;
		return p;
	}

	// -----------------------------------------------------------------------------

	Point Circle::getPointDirection(Directions d)
	{
		Point c = center();
		switch (d)
		{
		case NW:
			return getPointOnCircle(135);
		case N:
			return Point(c.x, c.y - r);
		case NE:
			return getPointOnCircle(45);
		case E:
			return Point(c.x + r, c.y);
		case SE:
			return getPointOnCircle(315);
		case S:
			return Point(c.x, c.y + r);
		case SW:
			return getPointOnCircle(225);
		case W:
			return Point(c.x - r, c.y);
		case CENTER:
			return center();
		default:
			error("That's an odd direction");
			break;
		}
	}

	//------------------------------------------------------------------------------

	void Striped_circle::validateCircle()
	{
		if (m_stripeWidth > (radius() * 2))
			error("Stripe width cannot be more than diameter.");
		if (m_stripeWidth < 1)
			error("Stripe width must be at least 1 pixel wide.");
	}

	// -----------------------------------------------------------------------------

	void Striped_circle::draw_lines() const
	{
		//striped fill
		//how many lines can we have?
		const int numOfLines = (diam() / m_stripeWidth) / 2;
		const int centerX = center().x;
		const int centerY = center().y;
		const int rad = radius();

		//set the colour for the lines(fill)
		fl_color(fill_color().as_int());

		//Y pos of first line starts at center - radius
		int lineYpos = centerY - rad;
		for (int i = 0; i < numOfLines; ++i)
		{
			for (int n = 0; n < m_stripeWidth; ++n)
			{
				int y = centerY - lineYpos;			//length of y, not position
				int x = getSqrt(rad*rad - y * y);	//length of x, not position
				fl_line(centerX - x, lineYpos, centerX + x, lineYpos);	//now calculate co-ordinates
				++lineYpos;							//increase for every line we draw
			}
			//skip stripe width
			lineYpos += m_stripeWidth;
		}

		//outline
		if (color().visibility())
		{
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, diam() + 1, diam() + 1, 0, 360);
		}
	}

	// -----------------------------------------------------------------------------

	void Smiley::draw_lines() const
	{
		//circle fill color && outline
		Circle::draw_lines();

		const int halfR = radius() / 2;
		//eyes
		if (fill_color().visibility())
		{
			const int eyeR = (radius() / 10) * 2;	//eyes are 20% the size of the radius

			fl_color(Color::black);
			fl_pie(point(0).x + halfR, point(0).y + halfR, eyeR, eyeR, 0, 360);
			fl_pie(point(0).x + radius() + halfR - eyeR, point(0).y + halfR, eyeR, eyeR, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		//mouth
		if (color().visibility())
		{
			const int mouthR = radius();
			fl_color(Color::black);
			fl_arc(point(0).x + halfR, point(0).y + halfR, mouthR, mouthR, 180, 360);
		}
	}

	// -----------------------------------------------------------------------------

	void SmileyHat::initHat()
	{
		p = new Fl_PNG_Image("cowboyHat.png");
		p = p->copy(radius() * 2, radius());
	}

	// -----------------------------------------------------------------------------

	void SmileyHat::draw_lines() const
	{
		Smiley::draw_lines();

		//'appropriate hat'
		p->draw(center().x - radius(), point(0).y - (radius() / 2));
	}

	// -----------------------------------------------------------------------------

	void Frowny::draw_lines() const
	{
		//circle fill color && outline
		Circle::draw_lines();

		const int halfR = radius() / 2;
		//eyes
		if (fill_color().visibility())
		{
			const int eyeR = (radius() / 10) * 2;	//eyes are 20% the size of the radius

			fl_color(Color::black);
			fl_pie(point(0).x + halfR, point(0).y + halfR, eyeR, eyeR, 0, 360);
			fl_pie(point(0).x + radius() + halfR - eyeR, point(0).y + halfR, eyeR, eyeR, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		//mouth
		if (color().visibility())
		{
			const int mouthR = radius();
			fl_color(Color::black);
			fl_arc(point(0).x + halfR, point(0).y + radius(), mouthR, mouthR, 0, 180);
		}
	}

	// -----------------------------------------------------------------------------

	void FrownyHat::initHat()
	{
		p = new Fl_PNG_Image("scumbagSteveHat.png");
		p = p->copy(radius() * 2, radius());
	}

	// -----------------------------------------------------------------------------

	void FrownyHat::draw_lines() const
	{
		Frowny::draw_lines();

		//'appropriate hat'
		p->draw(center().x - radius(), point(0).y - (radius() / 2));
	}

	// -----------------------------------------------------------------------------

	void Ellipse::draw_lines() const
	{
		if (fill_color().visibility())
		{	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w + w, h + h, 0, 360);
		}
	}

	// -----------------------------------------------------------------------------

	Point Ellipse::getPointOnEllipse(int angle)
	{
		Point p;
		double rad = angle * (PI / 180.0f);
		p.x = w * cos(rad) + center().x;
		p.y = h * sin(rad) + center().y;
		return p;
	}

	// -----------------------------------------------------------------------------

	Point Ellipse::getPointDirection(Directions d)
	{
		Point c = center();
		switch (d)
		{
		case NW:
			return getPointOnEllipse(135);
		case N:
			return Point(c.x, c.y - h);
		case NE:
			return getPointOnEllipse(45);
		case E:
			return Point(c.x + w, c.y);
		case SE:
			return getPointOnEllipse(315);
		case S:
			return Point(c.x, c.y + h);
		case SW:
			return getPointOnEllipse(225);
		case W:
			return Point(c.x - w, c.y);
		case CENTER:
			return center();
		default:
			error("That's an odd direction");
			break;
		}
	}

	//------------------------------------------------------------------------------

	void Arc::draw_lines() const
	{
		if (fill_color().visibility())
		{	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, w, h, angle1, angle2);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w, h, angle1, angle2);
		}
	}

	// -----------------------------------------------------------------------------

	void Arc::change_angle(int a1, int a2)
	{
		angle1 = a1;
		angle2 = a2;
		Arc::draw_lines();
	}

	// -----------------------------------------------------------------------------

	void draw_mark(Point xy, char c)
	{
		static const int dx = 4;
		static const int dy = 4;
		string m(1, c);
		fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
	}

	//------------------------------------------------------------------------------

	void Marked_polyline::draw_lines() const
	{
		Open_polyline::draw_lines();
		for (int i = 0; i < number_of_points(); ++i)
			draw_mark(point(i), mark[i%mark.size()]);
	}

	// -----------------------------------------------------------------------------

	void Mark::draw_lines() const
	{
		for (int i = 0; i < number_of_points(); ++i)
			fl_draw(mark.c_str(), point(i).x - 4, point(i).y + 4);
	}

	//------------------------------------------------------------------------------

	std::map<string, Suffix::Encoding> suffix_map;

	int init_suffix_map()
	{
		suffix_map["jpg"] = Suffix::jpg;
		suffix_map["JPG"] = Suffix::jpg;
		suffix_map["jpeg"] = Suffix::jpg;
		suffix_map["JPEG"] = Suffix::jpg;
		suffix_map["gif"] = Suffix::gif;
		suffix_map["GIF"] = Suffix::gif;
		suffix_map["bmp"] = Suffix::bmp;
		suffix_map["BMP"] = Suffix::bmp;
		suffix_map["png"] = Suffix::png;
		suffix_map["PNG"] = Suffix::png;
		return 0;
	}

	//------------------------------------------------------------------------------

	Suffix::Encoding get_encoding(const string& s)
		// try to deduce type from file name using a lookup table
	{
		static int x = init_suffix_map();

		string::const_iterator p = find(s.begin(), s.end(), '.');
		if (p == s.end()) return Suffix::none;	// no suffix

		string suf(p + 1, s.end());
		return suffix_map[suf];
	}

	//------------------------------------------------------------------------------

	ifstream can_open(const string& s)
		// check if a file named s exists and can be opened for reading
	{
		ifstream ff(s.c_str());
		return ff;
	}

	//------------------------------------------------------------------------------

	// somewhat overelaborate constructor
	// because errors related to image files can be such a pain to debug
	Image::Image(Point xy, string s, Suffix::Encoding e)
		:w(0), h(0), fn(xy, "")
	{
		add(xy);

		if (!can_open(s))
		{
			fn.set_label("cannot open \"" + s + '\"');
			p = new Bad_image(30, 20);	// the "error image"
			return;
		}

		if (e == Suffix::none) e = get_encoding(s);

		switch (e)
		{
		case Suffix::jpg:
			p = new Fl_JPEG_Image(s.c_str());
			break;
		case Suffix::gif:
			p = new Fl_GIF_Image(s.c_str());
			break;
		case Suffix::png:
			p = new Fl_PNG_Image(s.c_str());
			break;
			//	case Suffix::bmp:
			//		p = new Fl_BMP_Image(s.c_str());
			//		break;
		default:	// Unsupported image encoding
			fn.set_label("unsupported file type \"" + s + '\"');
			p = new Bad_image(30, 20);	// the "error image"
		}
	}

	//------------------------------------------------------------------------------

	void Image::draw_lines() const
	{
		if (fn.label() != "") fn.draw_lines();

		if (w&&h)
			p->draw(point(0).x, point(0).y, w, h, cx, cy);
		else
			p->draw(point(0).x, point(0).y);
	}

	//------------------------------------------------------------------------------

	void Box::draw_lines() const
	{
		const int radius = round >> 1;
		const int lineW = w - round;
		const int lineH = h - round;

		Point arc1(point(0).x, point(0).y);
		Point arc2(point(0).x + lineW, point(0).y);
		Point arc3(point(0).x + lineW, point(0).y + lineH);
		Point arc4(point(0).x, point(0).y + lineH);

		Line l1(Point{ arc1.x + radius, arc1.y }, Point{ arc2.x + radius, arc2.y });
		Line l2(Point{ arc2.x + round, arc2.y + radius }, Point{ arc2.x + round, arc3.y + radius });
		Line l3(Point{ arc2.x + radius, arc3.y + round }, Point{ arc4.x + radius, arc4.y + round });
		Line l4(Point{ arc4.x, arc4.y + radius }, Point(arc4.x, arc1.y + radius));

		if (fill_color().visibility())
		{	// fill
			fl_color(fill_color().as_int());
			fl_pie(arc1.x, arc1.y, round, round, 90, 180);
			fl_pie(arc2.x, arc2.y, round, round, 0, 90);
			fl_pie(arc3.x, arc3.y, round, round, 270, 360);
			fl_pie(arc4.x, arc4.y, round, round, 180, 270);

			fl_rectf(arc1.x, arc1.y + radius, radius, lineH);
			fl_rectf(arc1.x + radius, arc1.y, lineW, h);
			fl_rectf(arc2.x + radius, arc2.y + radius, radius, lineH);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{
			//top left-hand corner (arc)
			fl_arc(arc1.x, arc1.y, round, round, 90, 180);
			//top horizontal line
			fl_line(l1.point(0).x, l1.point(0).y, l1.point(1).x, l1.point(1).y);

			//top right-hand corner (arc)
			fl_arc(arc2.x, arc2.y, round, round, 0, 90);
			//right-hand vertical line
			fl_line(l2.point(0).x, l2.point(0).y, l2.point(1).x, l2.point(1).y);

			//bottom right-hand corner (arc)
			fl_arc(arc3.x, arc3.y, round, round, 270, 360);
			//bottom vertical line
			fl_line(l3.point(0).x, l3.point(0).y, l3.point(1).x, l3.point(1).y);

			//bottom left-hand corner (arc)
			fl_arc(arc4.x, arc4.y, round, round, 180, 270);
			//left-hand vertical line
			fl_line(l4.point(0).x, l4.point(0).y, l4.point(1).x, l4.point(1).y);
		}
	}

	// -----------------------------------------------------------------------------

	void Arrow::draw_lines() const
	{
		double halfA = arrowSize / 2;
		Point p1(point(0).x, point(0).y);	//begin line
		Point p2(point(1).x, point(1).y);	//tip of arrow

		//distance from p1 to p2
		double distance = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
		//arrow size distance away from p2
		Point p3(halfA / distance * p1.x + (1 - halfA / distance)*p2.x,
			halfA / distance * p1.y + (1 - halfA / distance)*p2.y);		//mid base of arrow

		//'left' arrow point
		double lx = p3.x + ((halfA * (p2.y - p1.y)) / distance);
		double ly = p3.y + ((halfA * (p1.x - p2.x)) / distance);

		//'right' arrow point
		double rx = p3.x + ((halfA * (p1.y - p2.y)) / distance);
		double ry = p3.y + ((halfA * (p2.x - p1.x)) / distance);

		if (fill_color().visibility())
		{
			// fill
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			fl_vertex(p2.x, p2.y);
			fl_vertex(lx, ly);
			fl_vertex(rx, ry);
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{
			//lines
			fl_line(p1.x, p1.y, p3.x, p3.y);
			fl_line(lx, ly, rx, ry);
			fl_line(p2.x, p2.y, rx, ry);
			fl_line(lx, ly, p2.x, p2.y);
		}
	}

	// -----------------------------------------------------------------------------

	void TextBox::setColours(Color boxOutline, Color boxFill, Color textColor)
	{
		box.set_color(boxOutline);
		box.set_fill_color(boxFill);
		set_color(textColor);
	}

	// -----------------------------------------------------------------------------

	void TextBox::draw_lines() const
	{
		box.draw_lines();

		Text::draw_lines();
	}

	// -----------------------------------------------------------------------------

	void Regular_Hexagon::draw_lines() const
	{
		if (number_of_points() < 6)
			error("less than 6 points in a Hexagon");
		Polygon::draw_lines();
	}

	// -----------------------------------------------------------------------------

	void Regular_Hexagon::hexagonTile(vector<Regular_Hexagon>& v, int numHex, int radius, int widthTile, Point p)
	{
		double twoR = radius + radius;
		double sideLength = twoR * sin(PI / 6);
		double edge = p.x + widthTile;
		double apothem = radius * cos(PI / 6);
		bool flipflop = 0;

		for (int i = 0; i < numHex; ++i)
		{
			Regular_Hexagon hex(p, radius);
			hex.set_color(Color::black);
			hex.set_fill_color(i);
			v.push_back(hex);
			p.x += twoR + sideLength;
			if (p.x > edge)
			{
				flipflop = !flipflop;
				p.x = flipflop * (radius + (sideLength / 2));
				p.y += apothem;
			}
		}
	}

	// -----------------------------------------------------------------------------

	void Regular_Octagon::draw_lines() const
	{
		if (number_of_points() < 8)
			error("less than 8 points in an Octagon");
		Polygon::draw_lines();
	}

	// -----------------------------------------------------------------------------

	void RightTriangle::rightTriangleTileWindow(vector<RightTriangle>& v, int sideLength)
	{
		RightTriangle rt1(Point(0, 0), Point(0, sideLength), Point(sideLength, sideLength), Color::black, Color::black);
		RightTriangle rt2(Point(0, 0), Point(sideLength, 0), Point(sideLength, sideLength), Color::cyan, Color::cyan);

		for (int y = 0; y < y_max(); y += sideLength)
		{
			for (int x = 0; x < x_max(); x += sideLength)
			{
				rt1.set_point(0, Point(x, y));
				rt1.set_point(1, Point(x, y + sideLength));
				rt1.set_point(2, Point(x + sideLength, y + sideLength));

				rt2.set_point(0, Point(x, y));
				rt2.set_point(1, Point(x + sideLength, y));
				rt2.set_point(2, Point(x + sideLength, y + sideLength));

				v.push_back(rt1);
				v.push_back(rt2);
			}
		}
	}

	// -----------------------------------------------------------------------------

	// ensure that all the angles add up to 180 and one of them is 90.
	// abs() flips int negatives to positive
	void RightTriangle::validateTriangle(Point p1, Point p2, Point p3)
	{
		a1 = findAngleBetween2Lines(p1, p2, p1, p3);
		a2 = findAngleBetween2Lines(p1, p2, p2, p3);
		a3 = findAngleBetween2Lines(p2, p3, p1, p3);
		int totalAngles = (a1 + a2 + a3);
		if (totalAngles != 180)
			error("All the angles in a right-triangle should add up to 180. This one adds up to " + totalAngles);
		if (a1 != 90 && a2 != 90 && a3 != 90)
			error("One of the angles must be equal to 90 degrees.");
	}

	// -----------------------------------------------------------------------------

	Star::Star(Point center, double outerRadius, double innerRadius, double startAngle, int numOfPoints)
		: m_center(center)
	{
		if (numOfPoints < 4)
			error("Cannot have less than 4 points on a star");

		int doubleNumPoints = numOfPoints * 2;
		double angle = 360.0f / doubleNumPoints;
		double rotation = startAngle;
		bool flipflop = true;

		for (int i = 0; i < doubleNumPoints; ++i)
		{
			if (flipflop)
				add(getPointOnStar(rotation, outerRadius));
			else
				add(getPointOnStar(rotation, innerRadius));

			rotation += angle;
			flipflop = !flipflop;
		}
	}

	// -----------------------------------------------------------------------------

	Point Star::getPointOnStar(int angle, double radius)
	{
		Point p;
		double rad = angle * (PI / 180.0f);
		p.x = radius * cos(rad) + (m_center.x);
		p.y = radius * sin(rad) + (m_center.y);
		return p;
	}

	// -----------------------------------------------------------------------------

	//helper function for sorting vectors of Points
	bool compareByX(const Point& a, const Point& b)
	{
		return a.x < b.x;
	}

	// -----------------------------------------------------------------------------

	bool compareByY(const Point& a, const Point& b)
	{
		return a.y < b.y;
	}

	// -----------------------------------------------------------------------------

	Group::Group()
	{
		m_light = new Fl_PNG_Image("cream.png");
		m_dark = new Fl_PNG_Image("dark.png");
		m_board = new Fl_JPEG_Image("board.jpg");

		bool flipflop = true;
		for (double y = 15; y < 220; y += 100)
		{
			for (double x = 115; x < 720; x += 200)
			{
				if(flipflop)
					v_light.push_back(Rectangle(Point{ x,y }, 70, 70));
				else
					v_light.push_back(Rectangle(Point{ x - 100,y }, 70, 70));
			}
			flipflop = !flipflop;
		}

		flipflop = true;
		for (double y = 515; y < 720; y += 100)
		{
			for (double x = 15; x < 720; x += 200)
			{
				if (flipflop)
					v_dark.push_back(Rectangle(Point{ x , y }, 70, 70));
				else
					v_dark.push_back(Rectangle(Point{ x + 100,y }, 70, 70));
			}
			flipflop = !flipflop;
		}
	}

	// -----------------------------------------------------------------------------

	void Group::draw_lines() const
	{
		//draw the board
		m_board->draw(0, 0);

		//draw pieces
		for (int i = 0; i < v_light.size(); ++i)
		{
			m_light->draw(v_light[i].point(0).x, v_light[i].point(0).y);
		}
		for (int i = 0; i < v_dark.size(); ++i)
		{
			m_dark->draw(v_dark[i].point(0).x, v_dark[i].point(0).y);
		}
	}

	// -----------------------------------------------------------------------------

	void Group::moveLightPiece(MoveDir direction, int pieceNum)
	{
		switch (direction)
		{
		case NorthEast:
			v_light[pieceNum].set_point(0, Point{ v_light[pieceNum].point(0).x + 100, v_light[pieceNum].point(0).y - 100 });
			break;
		case SouthEast:
			v_light[pieceNum].set_point(0, Point{ v_light[pieceNum].point(0).x + 100, v_light[pieceNum].point(0).y + 100 });
			break;
		case SouthWest:
			v_light[pieceNum].set_point(0, Point{ v_light[pieceNum].point(0).x - 100, v_light[pieceNum].point(0).y + 100 });
			break;
		case NorthWest:
			v_light[pieceNum].set_point(0, Point{ v_light[pieceNum].point(0).x - 100, v_light[pieceNum].point(0).y - 100 });
			break;
		default:
			error("That's a weird direction");
			break;
		}
	}

	// -----------------------------------------------------------------------------

	void Group::moveDarkPiece(MoveDir direction, int pieceNum)
	{

		switch (direction)
		{
		case NorthEast:
			v_dark[pieceNum].set_point(0, Point{ v_dark[pieceNum].point(0).x + 100, v_dark[pieceNum].point(0).y - 100 });
			break;
		case SouthEast:
			v_dark[pieceNum].set_point(0, Point{ v_dark[pieceNum].point(0).x + 100, v_dark[pieceNum].point(0).y + 100 });
			break;
		case SouthWest:
			v_dark[pieceNum].set_point(0, Point{ v_dark[pieceNum].point(0).x - 100, v_dark[pieceNum].point(0).y + 100 });
			break;
		case NorthWest:
			v_dark[pieceNum].set_point(0, Point{ v_dark[pieceNum].point(0).x - 100, v_dark[pieceNum].point(0).y - 100 });
			break;
		default:
			error("That's a weird direction");
			break;
		}
	}

	// -----------------------------------------------------------------------------
	
	void Group::removePiece(int pieceNum)
	{
		v_dark.erase(v_dark.begin() + pieceNum);
	}

	// -----------------------------------------------------------------------------

	void Pseudo_window::draw_lines() const
	{
		m_window2.draw_lines();
		m_window.draw_lines();		
		m_clip.draw_lines();
		label.draw_lines();
	}

	// -----------------------------------------------------------------------------

	void Binary_tree::draw_lines() const
	{
		switch (m_nodeType)
		{
		case NODE_circle: default:
			{
				for (int i = 0; i < v_nodes.size(); ++i)
				{
					v_nodes[i].draw_lines();
				}
				break;
			}
			case NODE_triangle:
			{
				for (int i = 0; i < v_nodes.size(); ++i)
				{
					EquilateralTriangle et(Point(v_nodes[i].center()), v_nodes[i].radius());
					et.set_color(Color::black);
					et.draw_lines();
				}
				break;
			}
			case NODE_square:
			{
				for (int i = 0; i < v_nodes.size(); ++i)
				{
					Point p(v_nodes[i].center().x - v_nodes[i].radius(), v_nodes[i].center().y - v_nodes[i].radius());
					Rectangle rect(p, v_nodes[i].diam(), v_nodes[i].diam());
					rect.set_color(Color::black);
					rect.draw_lines();
				}
				break;
			}
		}

		//draw as a line or draw as an arrow
		if (!m_useArrowLine)
		{
			for (int i = 0; i < v_lines.size(); ++i)
			{
				fl_line(v_lines[i].point(0).x, v_lines[i].point(0).y, v_lines[i].point(1).x, v_lines[i].point(1).y);
			}
		}
		else
		{
			for (int i = 0; i < v_lines.size(); ++i)
			{
				Arrow arrow(v_lines[i].point(0), v_lines[i].point(1), 10);
				arrow.set_color(m_arrowColour);
				arrow.set_fill_color(m_arrowColour);
				//arrow pointing up
				if (m_arrowDirection)
					arrow.draw_lines();
				//else arrow pointing down
				else
				{
					arrow.moveArrow(v_lines[i].point(1), v_lines[i].point(0));
					arrow.draw_lines();
				}
			}
		}
	}

	// -----------------------------------------------------------------------------

	//use 0 for down, and 1 for up
	void Binary_tree::setLineAsArrow(bool direction, Color col)
	{
		m_useArrowLine = true;
		m_arrowDirection = direction;
		m_arrowColour = col;
	}

	// -----------------------------------------------------------------------------

	//this is not great
	void Binary_tree::initNodes()
	{	
		int temp = 1;
		for (int i = 0; i < m_levels; ++i)
		{
			v_numOnEachLine.push_back(temp);
			temp *= 2;
		}
		//reversing vector to start on bottom line of nodes
		std::reverse(v_numOnEachLine.begin(), v_numOnEachLine.end());

		int radius = 10 * m_treeSize;
		int cf = 20 * m_treeSize;	//circumference
		int diffX = 0;
		int diffY = 20 * m_treeSize;
		//start with bottom layer - make it centered (i.e top node should be center of the window)
		int startX = (800 / 2) -(cf*v_numOnEachLine[0]);
		int startY = (((m_levels - 1) * diffY) * 2) + diffY;
		Point p(startX, startY + (m_offset - startY));
		Point start = p;
		//if there is only 1 node, set the correct Y
		if (p.y == 0)
			p.y = diffY;

		//create an equal distance between each node based on how many nodes there are
		diffX = (((v_numOnEachLine[0] * cf) * 2) / v_numOnEachLine[0]);
		fl_color(Color::black);

		int tempCircRad = 5 * m_treeSize;
		for (int i = 0; i < m_levels - 1; ++i)
		{
			for (int j = 0; j < v_numOnEachLine[i]; ++j)
			{
				//draw node
				Circle temp(Point(p.x, p.y), tempCircRad);
				if ((j & 1) == 0)
				{
					Circle temp2(Point((start.x + (diffX / 2))+(diffX*j), start.y - diffY), tempCircRad);
					v_lines.push_back(Line(Point(temp.getPointDirection(Directions::N)), Point(temp2.getPointDirection(Directions::S))));
					v_lines.push_back(Line(Point(temp.point(0).x + diffX + tempCircRad, temp.point(0).y), Point(temp2.getPointDirection(Directions::S))));
				}
				v_nodes.push_back(temp);
				//prevents diffX from being incremented after last node on line
				if (j < v_numOnEachLine[i] - 1)
					p.x += diffX;
			}
			//line above starting point should be halfway between first && second node on line that was just drawn
			p.x = start.x + (diffX / 2);
			p.y = start.y - diffY;
			start = p;
			//determine the new distance needed to keep nodes equal
			diffX *= 2;
		}
		//draw top node
		v_nodes.push_back(Circle(Point(p.x, p.y), tempCircRad));
	}

} // namespace Graph_lib

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
