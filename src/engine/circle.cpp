#include "circle.h"
#include <cmath>
#include "log.h"

Circle::Circle(int radius, bool filled)
:DrawableObject(MIN_WIDTH, MIN_HEIGHT)
{
	this->radius = radius;
	this->filled = filled;

	height = width = radius * 2;
}

Circle::~Circle() {}

void Circle::putObjectInSurface()
{
	int xInitial = this->radius, yInitial = this->radius;
	
	for(int i = 0; i < 360; i++)
	{
		int xFinal = this->getFinalX(i, this->radius) + xInitial;
		int yFinal = height - (this->getFinalY(i, this->radius) + yInitial);
		SDL_RenderDrawPoint(render->getRenderer(), xFinal, yFinal);
	}
}

int
Circle::getFinalX(int a, int r)
{
	return r*sin((90 - a)*M_PI/180);
}

int
Circle::getFinalY(int a, int r)
{
	return r*sin(a*M_PI/180);
}

