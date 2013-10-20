#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2/SDL_image.h"
#include "renderableobject.h"
#include <string>

class Image: virtual public RenderableObject{
public:
	Image(std::string, Render *, int = 1, int = 1, int = 1);
	~Image();
	
	std::string getImageId() const;

private:
	std::string imageId;

	SDL_Texture * generateTexture();
	SDL_Surface * loadImage();
};

#endif
