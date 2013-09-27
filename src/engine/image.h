#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2/SDL.h"

class Image{

public:
	Image();
	
	bool loadImage(const char* path, SDL_Renderer * render);
	SDL_Texture * getTexture();

private:
	SDL_Texture * texture;
	int width;
	int height;
};

#endif
