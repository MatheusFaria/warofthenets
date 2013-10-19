#include "image.h"
#include "log.h"

using namespace std;

Image::Image(string path, int sprites, int spritesLines, int spritesCols, Render * render)
:RenderableObject(render)
{
	this->imageId = path;
	this->sprites = sprites;
	this->spritesLines = spritesLines;
	this->spritesCols = spritesCols;
}

Image::~Image() {}

SDL_Surface *
Image::loadImage()
{
	return IMG_Load(this->imageId.c_str());
}	

SDL_Texture * 
Image::generateTexture()
{	
	SDL_Texture * imgTexture = NULL;
	SDL_Surface * imgSurface = this->loadImage();

	if(imgSurface != NULL)
	{
		imgTexture = SDL_CreateTextureFromSurface(getRenderer(), imgSurface);
		SDL_FreeSurface(imgSurface);
	}

	return imgTexture;
}

string 
Image::getImageId() const
{
	return this->imageId;
}

int 
Image::getNumberSprites() const
{
	return this->sprites;
}

int 
Image::getSpritesLines() const
{
	return this->spritesLines;
}

int 
Image::getSpritesColumns() const
{
	return this->spritesCols;
}

