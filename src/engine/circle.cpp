#include "circle.h"
#include "log.h"
#include "geometry.h"

Circle::Circle(int radius, Render * render)
:DrawableObject(render)
{
	this->radius = radius;

	setSurfaceWidth(radius * 2);
	setSurfaceHeight(radius * 2);
}

Circle::~Circle() {}


void Circle::putObjectInSurface()
{
	int xInitial = this->radius, yInitial = this->radius;
	int h = getSurfaceHeight();
	for(int i = 0; i < 360; i++)
	{
		int xFinal = Geometry::getLineEndX(i, this->radius) + xInitial;
		int yFinal = h - (Geometry::getLineEndY(i, this->radius) + yInitial);
		SDL_RenderDrawPoint(getInternalRenderer(), xFinal, yFinal);
	}
}

