// -----------------------------------------------------------------------------
// chrono.cpp
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "chrono.h"

// -----------------------------------------------------------------------------

namespace Chrono
{
	//member function definitions
	Date::Date(int y, Month m, int d)
		: m_y(y), m_m(m), m_d(d)
	{
		if (!is_date(y, m, d)) 
			error("Date is not valid");
	}

	// -----------------------------------------------------------------------------

	const Date& default_date()
	{
		static Date dd{ 2001, Month::jan, 1 };
		return dd;
	}

	// -----------------------------------------------------------------------------

	Date::Date()
		: m_y{ default_date().year() }
		, m_m{ default_date().month() }
		, m_d{ default_date().day() }
	{}

	// -----------------------------------------------------------------------------

	void Date::add_day(int n)
	{
		m_d += n;

		//what month are we?
		switch (m_m)
		{
			//30 days
			case Month::apr: case Month::jun: case Month::sep: case Month::nov:
				if (m_d > 30)
					m_d -= 30;
				break;
			//31 days
			case Month::jan: case Month::mar: case Month::may: case Month::jul: case Month::aug: case Month::oct: case Month::dec:
				if (m_d > 31)
					m_d -= 31;
				break;
			//February
			case Month::feb:
				if (leapyear(m_y) &&  (m_d > 29))
					m_d -= 29;
				else if (!leapyear(m_y) && (m_d > 28))
					m_d -= 28;
				break;
			default:
				cout << "Something weird happened in add_day()" << endl;
				break;
		}

		int nextM = int(m_m) + 1;
		if (nextM > 12)
		{
			add_month(1);
		}
		else
			m_m = Month(nextM);
	}

	// -----------------------------------------------------------------------------

	void Date::add_month(int n)
	{
		if (int nextM = int(m_m) + n > 12)
		{
			m_m = Month::jan;
			add_year(1);
		}
		else
			m_m = Month(nextM);
	}

	// -----------------------------------------------------------------------------

	void Date::add_year(int n)
	{
		m_y += n;
		if (m_y > 3000)
		{
			cout << "It is not the year 3000; busted" << endl;
			m_y -= n;
		}
	}

	// -----------------------------------------------------------------------------

	//helper functions
	bool is_date(int y, Month m, int d)
	{
		//assume that y is valid

		if (d <= 0)
			return false;
		if (m < Month::jan || Month::dec < m)
			return false;

		int days_in_month = 31;		//most months have 31 days

		switch (m)
		{
		case Month::feb:			//the length of February varies
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30;		//the rest have 30 days
			break;
		}

		if (days_in_month < d)
			return false;

		return true;
	}

	// -----------------------------------------------------------------------------

	//checks for leapyear (Gregorian calender)
	bool leapyear(int y)
	{
		// this is a bit confusing. Leap years are as defined:
		// if the year is evenly divisible by 4 (example: 2000 / 4 == 500 remainder 0)
		// century years are evenly divisible by 4, however they must also be evenly divisible by 400
		// (example: 1800 / 4 == 450 remainder 0 but 1800 / 400 == 4.5 remainder 0.5, therefore it is not a leap year,
		// however 2000 / 400 == 5 remainder 0, therefore it is a leap year)

		//if century year, must be divisible by 400
		if (y % 400 == 0) //remainder is 0
			return true;

		//if normal year and divisible by 4
		if (y % 4 == 0) //remainder is 0
			return true;

		//else not leap year
		return false;
	}

	// -----------------------------------------------------------------------------

	int daysSince1stJan(const Date& d)
	{
		int day = d.day();
		int month = int(d.month());
		int year = d.year();

		int result = 0;
		if (leapyear(year))
		{
			for (int i = 0; i < month - 1; ++i)
				result += daysInMonthLeap[i];
			result += day;
		}
		else
		{
			for (int i = 0; i < month - 1; ++i)
				result += daysInMonth[i];
			result += day;
		}

		return result; //-1 so todays date is not included in count
	}

	// -----------------------------------------------------------------------------

	//please ensure earliest date goes first
	long int howManyDaysBetweenDates(const Date& d1, const Date& d2)
	{
		//is the year the same?
		if (d1.year() == d2.year())
		{
			//if so just get the number of days left in d1 and subtract the number of days left in d2
			if (leapyear(d1.year()))
				return (366 - daysSince1stJan(d1)) - (366 - daysSince1stJan(d2));
			else
				return (365 - daysSince1stJan(d1)) - (366 - daysSince1stJan(d2));
		}
		else
		{
			long int daysBetween = 0;

			//get the days passed in the first year
			if (leapyear(d1.year()))
				daysBetween = 366 - daysSince1stJan(d1);
			else
				daysBetween = 365 - daysSince1stJan(d1);

			//get all the days in between d1.year + 1 till now
			for (int i = d1.year() + 1; i < d2.year(); ++i)
			{
				if (leapyear(i))
					daysBetween += 366;
				else
					daysBetween += 365;
			}

			//get all the passed in current year
			return daysBetween += daysSince1stJan(d2);
		}
	}

	// -----------------------------------------------------------------------------

	//assumes that any day that is not a saturday or sunday is a workday
	Day next_workday(const Date& d)
	{
		//what day is it?
		Date date = d;
		Day nextWorkDay = Day::monday;

		switch (day_of_the_week(d))
		{
		case Day::friday: case Day::saturday: case Day::sunday: 
			nextWorkDay = Day::monday;
			break;
		default:
			date.add_day(1);
			nextWorkDay = day_of_the_week(date);
			break;
		}

		return nextWorkDay;
	}

	// -----------------------------------------------------------------------------

	int week_of_year(const Date& d)
	{
		int day = d.day();
		int month = int(d.month());
		int year = d.year();

		int daysSince1st = daysSince1stJan(d);
		Day currentDay = day_of_the_week(d);
		Day dayOnJan1st = day_of_the_week(Date(d.year(), Month::jan, 1));

		int weekNum = ((daysSince1st + 6) / 7);
		if (int(currentDay) < int(dayOnJan1st))
			++weekNum;

		return weekNum;
	}

	// -----------------------------------------------------------------------------

	bool operator==(const Date& d1, const Date& d2)
	{
		return d1.year() == d2.year()
			&& d1.month() == d2.month()
			&& d1.day() == d2.day();
	}

	// -----------------------------------------------------------------------------

	bool operator!=(const Date& d1, const Date& d2)
	{
		return d1.year() != d2.year()
			&& d1.month() != d2.month()
			&& d1.day() != d2.day();
	}

	// -----------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << d.month()
			<< ',' << d.day() << ')';
	}

	// -----------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Month& m)
	{
		switch (m)
		{
		case Month::jan:
			return os << "January";
		case Month::feb:
			return os << "February";
		case Month::mar:
			return os << "March";
		case Month::apr:
			return os << "April";
		case Month::may:
			return os << "May";
		case Month::jun:
			return os << "June";
		case Month::jul:
			return os << "July";
		case Month::aug:
			return os << "August";
		case Month::sep:
			return os << "September";
		case Month::oct:
			return os << "October";
		case Month::nov:
			return os << "November";
		case Month::dec:
			return os << "December";
		default:
			return os << "Something weird happened.";
		}
	}

	// -----------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Day& d)
	{
		switch (d)
		{
		case Day::monday:
			return os << "Monday";
		case Day::tuesday:
			return os << "Tuesday";
		case Day::wednesday:
			return os << "Wednesday";
		case Day::thursday:
			return os << "Thursday";
		case Day::friday:
			return os << "Friday";
		case Day::saturday:
			return os << "Saturday";
		case Day::sunday:
			return os << "Sunday";
		default:
			return os << "Something weird happened in operator<<(Day).";
		}
	}

	// -----------------------------------------------------------------------------

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char c1, c2, c3, c4;
		is >> c1 >> y >> c2 >> m >> c3 >> d >> c4;
		if (!is)
			return is;
		if (c1 != '(' || c2 != ',' || c3 != ',' || c4 != ')')
		{
			is.clear(ios_base::failbit);		//format error: set the fail bit
			return is;
		}

		dd = Date(y, Month(m), d);				//update dd
		return is;
	}

	// -----------------------------------------------------------------------------

	Day day_of_the_week(const Date& date)
	{
		//these algorithms were taken from https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
		int day = date.day();
		int month = static_cast<int>(date.month());
		int year = date.year();

		//this one doesn't work correctly - it seems to be off by 1 day in certain cases
		//int dayOfWeek = (day += month < 3 ? --year : year - 2, 23 * month / 9 + day + 4 + year / 4 - year / 100 + year / 400) % 7;

		//this one works correctly, however it is accurate only for dates > 1752...
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		year -= month < 3;

		return Day((year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7);

	}

	// -----------------------------------------------------------------------------

	Date next_Sunday(const Date& d)
	{
		//to do:
		return d;
	}

	// -----------------------------------------------------------------------------

	Date next_weekday(const Date& d)
	{
		//to do:
		return d;
	}

	// -----------------------------------------------------------------------------
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
