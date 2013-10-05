#include "rectangle.h"
#include "log.h"

Rectangle::Rectangle(int w, int h, int posX, int posY, bool fill)
:DrawableObject(w, h, posX, posY)
{
	this->rect = {x, y, width, height};
	this->filled = fill;
}

Rectangle::~Rectangle()
{
}

void 
Rectangle::putObjectInSurface()
{
	if(this->filled)
		SDL_RenderFillRect(render->getRenderer(), &(this->rect));
	else
		SDL_RenderDrawRect(render->getRenderer(), &(this->rect));
}

void
Rectangle::fill()
{
	this->filled = true;
	draw();
}

