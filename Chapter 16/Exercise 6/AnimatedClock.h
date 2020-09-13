// -----------------------------------------------------------------------------
#ifndef ANIMATEDCLOCK_H_
#define ANIMATEDCLOCK_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------
	// currently hardcoded to work on 400x400 size window

	struct AnimatedClock : Shape
	{
	public:
		AnimatedClock(Point xy, string clock);

		void tick();
		void draw_lines() const;

	private:
		enum timeType {
			seconds, minutes, hours
		};

		Point getHourPoint(int t);
		Point getMinPoint(int t);
		Point getSecPoint(int t);
		Point getPointOnClock(int angle, int radius);

		int getAngle(int time, timeType tt);

		Image m_clockImage;
		Arrow m_hourHand;
		Arrow m_minuteHand;
		Arrow m_secondHand;
			
	};
	

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

#endif // !ANIMATEDCLOCK_H_
