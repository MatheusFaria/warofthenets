#include "pixel.h"
#include "log.h"

Pixel::Pixel() 
:DrawableObject(MIN_WIDTH, MIN_HEIGHT)
{}

Pixel::~Pixel() {}

void 
Pixel::putObjectInSurface()
{
	SDL_RenderDrawPoint(render->getRenderer(), x, y);
}
