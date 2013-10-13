#include "image.h"
#include "log.h"

Image::Image()
{
	this->texture = NULL;
	this->x = 0;
	this->y = 0;
}

Image::~Image()
{
	if(this->texture != NULL)
		SDL_DestroyTexture(texture);
}

bool
Image::loadImage(const char* path, SDL_Renderer * renderer)
{
	SDL_Surface * imgloaded = IMG_Load(path);

	if(imgloaded != NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, imgloaded);
		
		this->width = imgloaded->clip_rect.w;
		this->height = imgloaded->clip_rect.h;
		
		SDL_FreeSurface(imgloaded);
		if(this->texture == NULL)
			Log::warn("Could not create the texture from the surface");
	}
	else
		Log::warn("Could not load the image");
	return texture;
}	

SDL_Texture *
Image::getTexture()
{
	return this->texture;
}

int
Image::getWidth()
{
    return this->width;
}

int
Image::getHeight()
{
    return this->height;
}

int
Image::getX()
{
    return this->x;
}

void
Image::setX(int x)
{
    this->x = x;
}

int
Image::getY()
{
    return this->y;
}

void
Image::setY(int y)
{
    this->y = y;
}
	
