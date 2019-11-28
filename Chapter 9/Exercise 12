// -----------------------------------------------------------------------------
//
// C9 - Exercise 12
//
// instead of changing the implementation of Date, I added a new function which
// takes two dates and returns the numbers of days passed between them
//
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "chrono.h"

// -----------------------------------------------------------------------------

int main()
{
	using namespace Chrono;
	
	Date today{ 2019, Month::nov, 27 };
	Date today2{ 2019, Month::nov, 30 };
	Date jan1st{ 2019, Month::jan, 1 };

	cout << "Today is: " << day_of_the_week(today) << endl;
	cout << "Jan 1st was: " << day_of_the_week(jan1st) << endl;

	cout << "Days since Jan 1st: " << daysSince1stJan(today) << " (including today)" << endl;

	cout << "The current week number is: " << week_of_year(today) << endl;

	cout << "The number of days since Jan 1 1970 is: " << howManyDaysBetweenDates(Date(1970, Month::jan, 1), today) << endl;
	cout << "The number of days between today and today2: " << howManyDaysBetweenDates(today, today2) << endl;

	char ch;
	cin >> ch;
	return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
