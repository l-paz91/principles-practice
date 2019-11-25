// -----------------------------------------------------------------------------
// chrono.h
// -----------------------------------------------------------------------------
#ifndef _CHRONO_H_

//--INCLUDES--//
#include "std_lib_facilities.h"

using namespace std;

// -----------------------------------------------------------------------------

namespace Chrono
{
	enum class Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	enum class Day
	{
		monday, tuesday, wednesday, thursday, friday, saturday, sunday
	};

	class Date
	{
	public:
		Date(int y, Month m, int d);		//check for valid date and initialise
		Date();								//default constructor

		//non-modifying operations
		int day() const { return m_d; }
		Month month() const { return m_m; }
		int year() const { return m_y; }

		//modifying operations
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

	private:
		int m_y;
		Month m_m;
		int m_d;
	};

	bool is_date(int y, Month m, int d);		//true for valid date
	bool leapyear(int y);						//true if y is a leap year

	Day day_of_the_week(const Date& d);
	Date next_Sunday(const Date& d);
	Date next_weekday(const Date& d);

	bool operator==(const Date& d1, const Date& d2);
	bool operator!=(const Date& d1, const Date& d2);

	ostream& operator<<(ostream& os, const Date& d);
	ostream& operator<<(ostream& os, const Month& m);
	istream& operator>>(istream& is, Date& dd);

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !_CHRONO_H_


