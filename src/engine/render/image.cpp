#include "image.h"
#include "log.h"

using namespace std;

Image::Image(string path, Render * render, int sprites, int spritesLines, int spritesCols)
:RenderableObject(render, sprites, spritesLines, spritesCols)
{
	this->imageId = path;
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

