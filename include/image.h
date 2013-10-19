#ifndef IMAGE_H
#define IMAGE_H

#include "SDL2/SDL_image.h"
#include "renderableobject.h"
#include <string>

class Image: virtual public RenderableObject{
public:
	Image(std::string, int, int, int, Render *);
	~Image();
	
	std::string getImageId() const;
	int getNumberSprites() const;
	int getSpritesLines() const;
	int getSpritesColumns() const;

private:
	std::string imageId;
	int sprites;
	int spritesLines;
	int spritesCols;

	SDL_Texture * generateTexture();
	SDL_Surface * loadImage();
};

#endif
