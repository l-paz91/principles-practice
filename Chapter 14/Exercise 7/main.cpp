// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// Chapter 14 - Exercise 7
/*
	Define a Striped_closed_polyline using the technique from Striped_rectangle 
	(this requires some algorithmic inventiveness).
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;
typedef Graph_lib::Striped_closed_polyline SCP;
typedef Graph_lib::Polygon P;
// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 800, 800, "Exercise 7" };
	
	SCP scp682{ Point{ 50,50 }
			  , Point{ 50,150 }
			  , Point{ 150,50 }
			  , Point{ 150,150 } };
	scp682.set_color(Color::black);
	win.attach(scp682);

	SCP scp0102{
		Point{170, 50}, Point{270, 50},
		Point{170, 100}, Point{270, 150},
		Point{170, 200}, Point{270, 250},
		Point{170, 250}, Point{270, 200},
		Point{170, 150}, Point{270, 100}
	};
	scp0102.set_color(Color::black);
	win.attach(scp0102);

	SCP scp096{ Point(300, 50)
		, Point(600, 50)
		, Point(600, 250)
		, Point(450, 100)
		, Point(300, 250)
	};
	scp096.set_color(Color::black);
	win.attach(scp096);

	SCP billy{Point{ 300, 300 }
		, Point{ 400, 500 }
		, Point{ 100, 500 }
	};
	billy.set_color(Color::black);
	win.attach(billy);

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
