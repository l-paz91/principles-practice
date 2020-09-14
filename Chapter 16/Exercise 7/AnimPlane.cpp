// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "AnimPlane.h"

namespace Graph_lib
{
	// -----------------------------------------------------------------------------

	AnimPlane::AnimPlane(double xmax, double ymax)
		: m_planeImage(Point(0, 0), "airplane2.png")
		, m_planeFlipped(Point(0, 0), "airplane2flipped.png")
		, m_planeTrack(Point(xmax, ymax), xmax-100, ymax-50)
		, m_halfpw(m_planeImage.getWidth()/2)
		, m_halfph(m_planeImage.getHeight()/2)
		, m_angle(90)
	{
		//move plane to "ellipse track"
		Point p = m_planeTrack.getPointOnEllipse(m_angle);
		m_planeImage.changePoint(p.x- m_halfpw, p.y - m_halfph);

		m_planeTrack.set_color(Color::coral);
	}

	// -----------------------------------------------------------------------------

	void AnimPlane::tick()
	{
		++m_angle;
		Point p = m_planeTrack.getPointOnEllipse(m_angle);

		// decide which plane image to use
		if (m_angle > 0 && m_angle < 180)
			m_planeImage.changePoint(p.x - m_halfpw, p.y - m_halfph);
		else
			m_planeFlipped.changePoint(p.x - m_halfpw, p.y - m_halfph);
	
		if (m_angle == 360)
			m_angle = 0;
	}

	// -----------------------------------------------------------------------------

	void AnimPlane::draw_lines() const
	{
		if (m_angle > 0 && m_angle < 180)
		{
			m_planeImage.draw_lines();
		}
		else
			m_planeFlipped.draw_lines();
		
		//m_planeTrack.draw_lines();
	}

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


