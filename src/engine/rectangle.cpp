#include "rectangle.h"
#include "log.h"

Rectangle::Rectangle(int w, int h, Render * render, bool fill)
:DrawableObject(render, w, h)
{
	this->rect = {0, 0, w, h};
	this->filled = fill;
}

Rectangle::~Rectangle() {}

void 
Rectangle::putObjectInSurface()
{
	if(this->filled)
		SDL_RenderFillRect(getInternalRenderer(), &(this->rect));
	else
		SDL_RenderDrawRect(getInternalRenderer(), &(this->rect));
}

