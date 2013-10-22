#include "hexagon.h"
#include "log.h"
#include <cmath>

Hexagon::Hexagon(int size, Render * render)
:DrawableObject(render)
{
	this->size = size;
	setSurfaceHeight(size*sin(60*M_PI/180)*2 + 1);
	setSurfaceWidth(size*2 + 1);
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
	int xInitial = this->size, yInitial = this->size*sin(60*M_PI/180);
	for(int i = 0, oldX = 0, oldY = 0; i <= 360; i+=60)
	{
		int newX = getFinalX(i, this->size) + xInitial;
		int newY = (getFinalY(i, this->size) + yInitial);
		if(i)
			SDL_RenderDrawLine(getInternalRenderer(), oldX, oldY, newX, newY);
		oldX = newX;
		oldY = newY;
	}

}



