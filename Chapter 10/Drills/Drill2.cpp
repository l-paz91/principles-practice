// -----------------------------------------------------------------------------
//
// C10 - Drill 2
/*
	Using the code and discussion in 10.4, prompt the user to input seven (x,y)
	pairs. As the data is entered, store it in a vector of Points called original
	points.
*/
// -----------------------------------------------------------------------------


//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct Point
{
	double x, y;
};

// -----------------------------------------------------------------------------

double getNumber()
{
	double d;
	//clears up cin if NaN was entered, taken from http://www.cplusplus.com/forum/beginner/21595/
	while (!(cin >> d))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Try again: ";
	}
	return d;
}

// -----------------------------------------------------------------------------

void getPoints(int loop, vector<Point>& points)
{
	Point p;
	for (int i = 0; i < loop; ++i)
	{
		cout << "Please enter " << loop << " pair(s) of points." << endl;
		cout << "Points " << i + 1 << endl;
		cout << "X: "; p.x = getNumber();
		cout << "Y: "; p.y = getNumber();
		points.push_back(p);
		system("CLS");			//please be aware this only works on windows
	}
}

// -----------------------------------------------------------------------------

int main()
{
	vector<Point> v_originalPoints;
	getPoints(7, v_originalPoints);

	//print points just for debugging purposes
	for (uint32_t i = 0; i < v_originalPoints.size(); ++i)
		cout << v_originalPoints[i].x << ", " << v_originalPoints[i].y << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
