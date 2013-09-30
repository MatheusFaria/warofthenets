#include "image.h"
#include "log.h"

Image::Image()
{
}

Image::~Image()
{
	if(this->texture != NULL)
		SDL_DestroyTexture(texture);
}

bool
Image::loadImage(const char* path, SDL_Renderer * renderer)
{
	SDL_Surface * imgloaded = SDL_LoadBMP(path);

	if(imgloaded != NULL)
	{
		this->texture = SDL_CreateTextureFromSurface(renderer, imgloaded);
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
	
