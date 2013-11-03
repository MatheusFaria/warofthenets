#include "pixel.h"
#include "log.h"

Pixel::Pixel(Render * render) 
:DrawableObject(render)
{
	setSurfaceWidth(1);
	setSurfaceHeight(1);
}
Pixel::~Pixel() {}

void 
Pixel::putObjectInSurface()
{
	SDL_RenderDrawPoint(getInternalRenderer(), 0, 0);
}
