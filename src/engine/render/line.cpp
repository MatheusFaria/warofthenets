#include "line.h"
#include <cmath>
#include "log.h"

Line::Line(int size, int angle, Render * render)
:DrawableObject(render)
{
	this->size = size;
	this->angle = angle;

	setSurfaceHeight(size*2);
	setSurfaceWidth(size*2);
}

Line::~Line() {}

int
getFinalX(int a, int r)
{
	return r*sin((90 - a)*M_PI/180);
}

int
getFinalY(int a, int r)
{
	return r*sin(a*M_PI/180);
}

void 
Line::putObjectInSurface()
{
	int xInitial = this->size, yInitial = this->size;
	int xFinal = getFinalX(this->size, this->angle) + xInitial;
	int yFinal = getSurfaceHeight() - (getFinalY(this->size, this->angle) + yInitial);
	
	SDL_RenderDrawLine(getInternalRenderer(), xInitial, yInitial,
											xFinal, yFinal);
}

