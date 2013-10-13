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
	
	int getWidth();
	int getHeight();
	
	int getX();
	void setX(int x);
	int getY();
	void setY(int y);

private:
	SDL_Texture * texture;
	
	int width;
	int height;
	
	int x;
	int y;
};

#endif
