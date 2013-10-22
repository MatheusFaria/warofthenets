#include "circle.h"
#include <cmath>
#include "log.h"

Circle::Circle(int radius, Render * render)
:DrawableObject(render)
{
	this->radius = radius;

	setSurfaceWidth(radius * 2);
	setSurfaceHeight(radius * 2);
}

Circle::~Circle() {}

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

void Circle::putObjectInSurface()
{
	int xInitial = this->radius, yInitial = this->radius;
	int h = getSurfaceHeight();
	for(int i = 0; i < 360; i++)
	{
		int xFinal = getFinalX(i, this->radius) + xInitial;
		int yFinal = h - (getFinalY(i, this->radius) + yInitial);
		SDL_RenderDrawPoint(getInternalRenderer(), xFinal, yFinal);
	}
}

