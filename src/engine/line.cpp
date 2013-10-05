#include "line.h"
#include <cmath>
#include "log.h"

Line::Line(int size, int angle)
:DrawableObject(MIN_WIDTH, MIN_HEIGHT)
{
	this->size = size;
	this->angle = angle;

	int xFinal = this->getFinalX();
	int yFinal = this->getFinalY();

	width = height = size*2;
	y = x = size;
}

Line::~Line() {}

void 
Line::putObjectInSurface()
{
	int xInitial = x, yInitial = y;
	int xFinal = this->getFinalX() + xInitial;
	int yFinal = height - (this->getFinalY() + yInitial);
	
	SDL_RenderDrawLine(render->getRenderer(), xInitial, yInitial,
											xFinal, yFinal);
}

int Line::getFinalX()
{
	return this->size*sin((90 - this->angle)*M_PI/180);
}

int Line::getFinalY()
{
	return this->size*sin((this->angle)*M_PI/180);
}

