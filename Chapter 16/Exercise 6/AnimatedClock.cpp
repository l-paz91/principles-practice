// -----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

//----INCLUDES----//
#include "AnimatedClock.h"

// -----------------------------------------------------------------------------
namespace Graph_lib
{
	Graph_lib::AnimatedClock::AnimatedClock(Point xy, string clock )
		: m_clockImage(xy, clock)
		, m_hourHand(Point(200,200), Point(200,70), 20)
		, m_minuteHand(Point(200, 200), Point(300, 200), 10)
		, m_secondHand(Point(200, 200), Point(300, 200), 5)
	{
		//set line style
		Line_style ls{ Line_style::solid, 2 };
		set_style(ls);
		m_hourHand.set_color(Color::black);
		m_hourHand.set_fill_color(Color::black);
		m_minuteHand.set_color(Color::blue);
		m_minuteHand.set_fill_color(Color::blue);
		m_secondHand.set_color(Color::dark_green);
		m_secondHand.set_fill_color(Color::dark_green);

		//get intial current time and change clock hands
		time_t t = time(0);
		tm* currentTime = localtime(&t);
		m_hourHand.moveArrow(Point(200, 200), getHourPoint(currentTime->tm_hour));
		m_minuteHand.moveArrow(Point(200, 200), getMinPoint(currentTime->tm_min));
		m_secondHand.moveArrow(Point(200, 200), getSecPoint(currentTime->tm_sec));
	}

	// -----------------------------------------------------------------------------

	void AnimatedClock::tick()
	{
		time_t t = time(0);
		tm* currentTime = localtime(&t);
		m_hourHand.moveArrow(Point(200, 200), getHourPoint(currentTime->tm_hour));
		m_minuteHand.moveArrow(Point(200, 200), getMinPoint(currentTime->tm_min));
		m_secondHand.moveArrow(Point(200, 200), getSecPoint(currentTime->tm_sec));
	}

	void AnimatedClock::draw_lines() const
	{
		m_clockImage.draw_lines();
		m_hourHand.draw_lines();
		m_minuteHand.draw_lines();
		m_secondHand.draw_lines();
	}

	// -----------------------------------------------------------------------------

	Point AnimatedClock::getHourPoint(int t)
	{
		int angle = getAngle(t, hours);
		return getPointOnClock(angle, 120);
	}

	// -----------------------------------------------------------------------------

	Point AnimatedClock::getMinPoint(int t)
	{
		int angle = getAngle(t, minutes);
		return getPointOnClock(angle, 90);
	}

	// -----------------------------------------------------------------------------

	Point AnimatedClock::getSecPoint(int t)
	{
		int angle = getAngle(t, seconds);
		return getPointOnClock(angle, 60);
	}

	// -----------------------------------------------------------------------------

	Point AnimatedClock::getPointOnClock(int angle, int radius)
	{
		Point p;
		double rad = angle * (PI / 180.0f);
		p.x = (radius * cos(rad) + (200));
		p.y = (radius * sin(rad) + (200));
		return p;
	}

	// -----------------------------------------------------------------------------

	int AnimatedClock::getAngle(int time, timeType tt)
	{
		switch (tt)
		{
		case seconds: case minutes:
			return (time * 6) - 90;
		case hours:
			return(time * 30) - 90;
		}
	}

	// -----------------------------------------------------------------------------
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
