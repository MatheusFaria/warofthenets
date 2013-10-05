#include "pixel.h"
#include "log.h"

#define MIN_HEIGTH 1
#define MIN_WIDTH  1

Pixel::Pixel(int xPos, int yPos) 
:DrawableObject(MIN_WIDTH, MIN_HEIGTH, xPos, yPos)
{}

Pixel::~Pixel() {}

void 
Pixel::putObjectInSurface()
{
	SDL_RenderDrawPoint(render->getRenderer(), x, y);
}
