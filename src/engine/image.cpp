#include "image.h"
#include <iostream>

using namespace std;

Image::Image()
{
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
			cout << "Could not create the texture from the surface " << path << " :: " << SDL_GetError() << endl;
	}
	else
		cout << "Could not load the image " << path << " :: " << SDL_GetError() << endl;
	return texture;
}	

SDL_Texture *
Image::getTexture()
{
	return this->texture;
}	
	
