#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Image{

public:
	Image();
	~Image();
	
	bool loadImage(const char* path, SDL_Renderer * render);
	SDL_Texture * getTexture();

private:
	SDL_Texture * texture;
};

#endif
