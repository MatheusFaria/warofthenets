#include "hexagon.h"
#include "log.h"
#include <cmath>

Hexagon::Hexagon(int size)
:DrawableObject(MIN_WIDTH, MIN_HEIGHT)
{
	this->size = size;
	height = size*2;
	width = size*2 + 1;
	//width = (height / sqrt(3)) + (2 * (height/ (2 * sqrt(3))));
}

Hexagon::~Hexagon() {}

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
Hexagon::putObjectInSurface()
{
	int xInitial = this->size, yInitial = this->size;
	for(int i = 0, oldX = 0, oldY = 0; i <= 360; i+=60)
	{
		int newX = getFinalX(i, this->size) + xInitial;
		int newY = height - (getFinalY(i, this->size) + yInitial);
		if(i)
			SDL_RenderDrawLine(render->getRenderer(), oldX, oldY, newX, newY);
		oldX = newX;
		oldY = newY;
	}

}



