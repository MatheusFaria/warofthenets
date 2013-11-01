#include "line.h"
#include "log.h"
#include "geometry.cpp"

Line::Line(int size, int angle, Render * render)
:DrawableObject(render)
{
	this->size = size;
	this->angle = angle;

	setSurfaceHeight(size*2);
	setSurfaceWidth(size*2);
}

Line::~Line() {}

void 
Line::putObjectInSurface()
{
	int xInitial = this->size, yInitial = this->size;
	int xFinal = Geometry::getLineEndX(this->size, this->angle) + xInitial;
	int yFinal = getSurfaceHeight() - (Geometry::getLineEndY(this->size, this->angle) + yInitial);
	
	SDL_RenderDrawLine(getInternalRenderer(), xInitial, yInitial,
											xFinal, yFinal);
}

