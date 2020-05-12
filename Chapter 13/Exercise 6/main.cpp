// -----------------------------------------------------------------------------
//
// Chapter 13 - Exercise 6
/*
	Write a program that draws a class diagram like the one in Section 12.6. It 
	will simplify matters if you start by defining a Box class that is a 
	rectangle with a text label.
	
	Edit 12/05/2020 - Please see the blog post for how to determine box width
	based on message length
	https://lptcp.blogspot.com/2020/04/chapter-13-exercise-6-principles.html
*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

int main()
{
	Simple_window win{ Point{100,100}, 1000, 900, "Chapter 13 - Exercise 6" };

	vector<Graph_lib::TextBox> v_tbs{
		TextBox{Point{ 200, 150 }, "Window", 20},
		TextBox{Point{ 300, 150 }, "Line_style", 20},
		TextBox{Point{ 450, 150 }, "Color", 20},
		TextBox{Point{ 150, 300 }, "Simple_window", 20},
		TextBox{Point{ 350, 250 }, "Shape", 20},
		TextBox{Point{ 450, 300 }, "Point", 20},
		TextBox{Point{ 100, 400 }, "Line", 20},
		TextBox{Point{ 200, 400 }, "Lines", 20},
		TextBox{Point{ 300, 400 }, "Polygon", 20},
		TextBox{Point{ 420, 400 }, "Axis", 20},
		TextBox{Point{ 500, 400 }, "Rectangle", 20},
		TextBox{Point{ 630, 400 }, "Text", 20},
		TextBox{Point{ 700, 400 }, "Image", 20}
	};

	for (int i = 0; i < v_tbs.size(); ++i)
	{
		v_tbs[i].setColours(Color::black, Color::green, Color::black);
		win.attach(v_tbs[i]);
	}
	
	//I haven't defined NESW etc for Box so doing it this way instead
	vector<Graph_lib::Arrow> v_arrows{
		Arrow{v_tbs[3].getTopCenter(), v_tbs[0].getBottomCenter(), 10},
		Arrow{v_tbs[6].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
		Arrow{v_tbs[7].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
		Arrow{v_tbs[8].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
		Arrow{v_tbs[9].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
		Arrow{v_tbs[10].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
		Arrow{v_tbs[11].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
		Arrow{v_tbs[12].getTopCenter(), v_tbs[5].getBottomCenter(), 10},
	};

	for (int i = 0; i < v_arrows.size(); ++i)
	{
		v_arrows[i].set_color(Color::black);
		v_arrows[i].set_fill_color(Color::black);
		win.attach(v_arrows[i]);
	}

	win.wait_for_button();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
