// -----------------------------------------------------------------------------
//
// C9 - Exercise 11
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "chrono.h"

// -----------------------------------------------------------------------------

int main()
{
	using namespace Chrono;
	
	Date today{ 2019, Month::nov, 26 };
	Date jan1st{ 2019, Month::jan, 1 };

	cout << "Today is: " << day_of_the_week(today) << endl;
	cout << "Jan 1st was: " << day_of_the_week(jan1st) << endl;

	cout << "Days since Jan 1st: " << daysSince1stJan(today) << " (including today)" << endl;

	cout << "The current week number is: " << week_of_year(today) << endl;

	today.add_day(10);
	cout << today << endl;
	today.add_month(2);
	cout << today << endl;
	today.add_year(6);
	cout << today << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
