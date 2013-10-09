#include "image.h"
#include "log.h"

Image::Image()
{
	this->texture = NULL;
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
		
		cout << "\n imgloaded->clip_rect.w: " << imgloaded->clip_rect.w << endl;
		cout << " imgloaded->clip_rect.h: " << imgloaded->clip_rect.h << endl;
		
		this->width = imgloaded->clip_rect.w;
		this->height = imgloaded->clip_rect.h;
		
		cout << "this->getWidth(): " << this->getWidth() << endl;
		cout << "this->getHeight(): " << this->getHeight() << endl << endl;
		
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
	
