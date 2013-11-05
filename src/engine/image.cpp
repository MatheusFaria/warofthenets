#include "image.h"
#include "log.h"

Image::Image(std::string imagePath, int x, int y, int numFrames)
: SDLGameObject(x, y, 0, 0, imagePath, imagePath, numFrames)
{
	
}
