// -----------------------------------------------------------------------------
// https://lptcp.blogspot.com/
// 
/*
	Chapter 22 - Exercise 15

	Write a program that, given a file of (name, year) pairs, such as (Algol,1960) 
	and (C,1974), graphs the names on a timeline.

*/
// https://github.com/l-paz91/principles-practice/tree/master/Graphics%20Files
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include <map>
#include <utility>

#include "Graph.h"
#include "Simple_window.h"

using namespace Graph_lib;

// -----------------------------------------------------------------------------

vector<std::pair<string, int>> readIn(const string& pFilename)
{
	vector<std::pair<string, int>> nameYearPair;

	ifstream readIn(pFilename);
	string line;
	getline(readIn, line);

	while (!readIn.eof())
	{
		// name
		string name = line.substr(1, (line.size() - 7));

		// year
		int year = stoi(line.substr((line.size() - 5), 4));

		nameYearPair.push_back(std::pair<string, int>(name, year));
		getline(readIn, line);
	}

	return nameYearPair;
}

// -----------------------------------------------------------------------------

bool sortByYear(std::pair<string, int> y1, std::pair<string, int> y2)
{
	return y1.second < y2.second;
}

// -----------------------------------------------------------------------------

int main()
{
	Simple_window window(Point(100, 100), 700, 600, "Chapter 22 - Exercise 15");

	auto v = readIn("NameYearPairs.txt");
	sort(v, sortByYear);

	Axis y(Axis::Orientation::y, Point(50, 570), 550, v.size(), "");

	vector<TextBox> vTextBoxes;
	Point p(Point(100, 350));
	int notches = 0;
	for (int i = v.size()-1; i >= 0; --i)
	{
		stringstream msg;
		msg << v[i].second << ", " << v[i].first;
		TextBox t(p, msg.str(), 5);
		t.set_fill_color(Color::yellow);
		p.y = y.getNotch(notches).y;
		vTextBoxes.push_back(TextBox(p, msg.str(), 5));
		notches += 2;
	}

	for (TextBox& t : vTextBoxes)
	{
		window.attach(t);
	}
	
	window.attach(y);

	return 	gui_main();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
