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
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection) {
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

	//------------------------------------------------------------------------------

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

	Point Rectangle::getPointDirection(Directions d)
	{
		switch (d)
		{
		case NW:
			return point(0);
		case N:
			return Point(point(0).x + (w / 2), point(0).y );
		case NE:
			return Point(point(0).x + w, point(0).y);
		case E:
			return Point(point(0).x + w, point(0).y + (h/2));
		case SE:
			return Point(point(0).x + w, point(0).y + h);
		case S:
			return Point(point(0).x + (w/2), point(0).y + h);
		case SW:
			return Point(point(0).x, point(0).y + h);
		case W:
			return Point(point(0).x, point(0).y + (h/2));
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
			fl_arc(point(0).x, point(0).y, r + r, r + r , 0, 360);
		}
	}

	// -----------------------------------------------------------------------------

	Point Circle::getPointOnCircle(int angle)
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
			return getPointOnCircle(315);
		case N:
			return Point(c.x, c.y - r);
		case NE:
			return getPointOnCircle(45);
		case E:
			return Point(c.x + r, c.y);
		case SE:
			return getPointOnCircle(135);
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
			return getPointOnEllipse(315);
		case N:
			return Point(c.x, c.y - h);
		case NE:
			return getPointOnEllipse(45);
		case E:
			return Point(c.x + w, c.y);
		case SE:
			return getPointOnEllipse(135);
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
		for (int i=0; i<number_of_points(); ++i)
			fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
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
			halfA / distance * p1.y + (1 -halfA / distance)*p2.y);		//mid base of arrow
	
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
		if (number_of_points() < numSides) 
			error("less than 6 points in a Hexagon");
		Polygon::draw_lines();
	}

} // namespace Graph_lib

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
