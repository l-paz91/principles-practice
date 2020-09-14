// -----------------------------------------------------------------------------
#ifndef ANIMPLANE_H_
#define ANIMPLANE_H_
// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "GUI.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------
	// shape contains an image of a plane that follows a "track" created by an ellipse

	struct AnimPlane : Shape
	{
	public:
		AnimPlane(double xmax, double ymax);

		void tick();
		void draw_lines() const;

	private:
		Image m_planeImage;
		Image m_planeFlipped;
		Ellipse m_planeTrack;
		double m_halfpw, m_halfph;
		int m_angle;
	};


}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------



#endif // !ANIMPLANE_H_

