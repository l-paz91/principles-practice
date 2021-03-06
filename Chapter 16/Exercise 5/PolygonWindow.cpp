// -----------------------------------------------------------------------------

//----INCLUDES----//
#include "PolygonWindow.h"

// -----------------------------------------------------------------------------

namespace Graph_lib
{
	// -----------------------------------------------------------------------------
	
	PolygonWindow::PolygonWindow(Point xy, int w, int h, const char * title)
		: Window(xy, w, h, title)
		, m_starShape(Point(-100,-100), 5, 5)
		, m_polygonM{ Point{0, 30}, 125, 20, Menu::horizontal, "Polygons" }
		, m_quitB(Point(x_max() - 70, 0), 70, 20, "Quit", 
			[](Address, Address addr) {reference_to<PolygonWindow>(addr).onQuitPressed(); })
		, m_nextB(Point(x_max() - 140, 0), 70, 20, "Next",
			[](Address, Address addr) {reference_to<PolygonWindow>(addr).onNextPressed(); })
		, m_xIn{ Point{15, 0}, 50, 20, "x:" }
		, m_yIn{ Point{80, 0}, 50, 20, "y:" }
		, m_sizeIn{Point{190, 0}, 50, 20, "radius: "}
	{
		// set up callbacks
		m_polygonM.attach(new Button{ Point(0,0), 0, 0, "circle",
			[](Address, Address addr) {reference_to<PolygonWindow>(addr).onCreatePolygon(PolygonType::circle); }});
		m_polygonM.attach(new Button{ Point(0,0), 0, 0, "square",
			[](Address, Address addr) {reference_to<PolygonWindow>(addr).onCreatePolygon(PolygonType::square); }});
		m_polygonM.attach(new Button{ Point(0,0), 0, 0, "equilateral triangle",
			[](Address, Address addr) {reference_to<PolygonWindow>(addr).onCreatePolygon(PolygonType::eqTriangle); }});
		m_polygonM.attach(new Button{ Point(0,0), 0, 0, "hexagon",
			[](Address, Address addr) {reference_to<PolygonWindow>(addr).onCreatePolygon(PolygonType::hexagon); } });

		// attach objects
		attach(m_starShape);
		attach(m_polygonM);
		attach(m_quitB);
		attach(m_nextB);
		attach(m_xIn);
		attach(m_yIn);
		attach(m_sizeIn);
	}

	// -----------------------------------------------------------------------------

	void PolygonWindow::onQuitPressed()
	{
		hide();		// fltk idiom to delete window
	}

	// -----------------------------------------------------------------------------

	void PolygonWindow::onNextPressed()
	{
		Point xy{ double(m_xIn.get_int()), double(m_yIn.get_int()) };
		if (xy.x == NO_NUMBER_GIVEN && xy.y == NO_NUMBER_GIVEN)
		{
			//draw a star somewhere randomly on the screen
			m_starShape = Star(Point(randint(0, x_max()), randint(0, y_max())), 
				randint(0, 100), randint(0, 100), randint(0, 100), randint(4, 12));
		}
		else
		{
			m_starShape = Star(xy,
				randint(0, 100), randint(0, 100), randint(0, 100), randint(4, 12));
		}

		m_starShape.set_color(randint(0, 255));
		m_starShape.set_fill_color(randint(0, 255));
		redraw();
	}

	// -----------------------------------------------------------------------------

	void PolygonWindow::onCreatePolygon(PolygonType pt)
	{
		Point xy{ double(m_xIn.get_int()), double(m_yIn.get_int()) };
		double radius = m_sizeIn.get_int();

		switch (pt)
		{
			case circle:
			{
				mv_shapes.push_back(new Circle { xy, int(radius) });
				mv_shapes.back()->set_color(Color::blue);
				break;
			}
			case square:
			{
				mv_shapes.push_back(new Graph_lib::Rectangle{ xy, radius, radius });
				mv_shapes.back()->set_color(Color::green);
				break;
			}
			case eqTriangle:
			{
				mv_shapes.push_back(new Graph_lib::EquilateralTriangle{ xy, radius});
				mv_shapes.back()->set_color(Color::coral);
				break;
			}			
			case hexagon:
			{
				mv_shapes.push_back(new Graph_lib::Regular_Hexagon{ xy, radius});
				mv_shapes.back()->set_color(Color::dark_yellow);
				break;
			}
		}

		attach(*mv_shapes.back());
		Fl::redraw();
	}

	// -----------------------------------------------------------------------------

}  // namespace Graph_lib

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

