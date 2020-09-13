// -----------------------------------------------------------------------------
#ifndef POINT_GUARD
#define POINT_GUARD

//typedef void (*Callback)(void*,void*);

// -----------------------------------------------------------------------------

namespace Graph_lib 
{
	struct Point 
	{
		//default constructor
		Point() :x(0), y(0) 
		{ }

		//constructor to initialise with doubles
		Point(double xx, double yy) : x(xx), y(yy) 
		{ }

		//constructor to initialise with ints (casts to double)
		//Point(int xx, int yy) : x(static_cast<double>(xx)), y(static_cast<double>(yy)) 
		//{ }

		double x, y;
		//	Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }
	};

	inline bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

	inline bool operator!=(Point a, Point b) { return !(a == b); }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
#endif