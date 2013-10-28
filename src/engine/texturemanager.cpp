#include "texturemanager.h"
#include <iostream>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

using namespace std;

TextureManager* TextureManager::instance = NULL;

TextureManager* 
TextureManager::Instance()
{
	if(TextureManager::instance == NULL)
	{
		instance = new TextureManager();
		return instance;
	}
	
	return instance;	
}

bool
TextureManager::loadImage(string imagePath,  string imageId, SDL_Renderer* renderer)
{
	map<std::string, SDL_Texture*>::iterator it;
	it = textureMap.find(imageId);

	if(it != textureMap.end())
	{
			textureCount[imageId]++;
			return true;
	}			

	SDL_Surface* surface = IMG_Load(imagePath.c_str());

	if(!surface)
	{
		cout<<"Error:"<<endl;
		//cout<<"Error: "<<SDL_GetError()<<endl;
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if(texture)
	{
		textureMap[imageId] = texture;
		textureCount[imageId]=1;
		return true;
	}
	else
	{
		cout<<"Error:"<<endl;
		return false;
	}

	

}

void
TextureManager::draw(string imageId, int x, int y,
	SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect source;
	SDL_Rect destination;

	if(textureMap.find(imageId) == textureMap.end())
	{
		cout<<"Couldn't find the respective image with id: "<<imageId<<endl;
		return;
	}

	source.x = source.y = 0;
	SDL_QueryTexture(textureMap[imageId], NULL, NULL, &source.w, &source.h);

	destination.w=source.w;
	destination.h=source.h;	
	destination.x = x;
	destination.y = y;

	SDL_RenderCopyEx(renderer, textureMap[imageId], &source, &destination, 0, 0, flip);

}

void
TextureManager::drawFrame(std::string imageId, int x, int y, int width, int height, int currentRow, 
	int currentFrame, SDL_Renderer *renderer , double angle, SDL_RendererFlip flip)
{
	SDL_Rect source;
	SDL_Rect destination;


	if(textureMap.find(imageId) == textureMap.end())
	{
		cout<<"Couldn't find the respective image with id: "<<imageId<<endl;
		return;
	}

    source.x = width * currentFrame;
    source.y = height * currentRow;

	destination.w=source.w = width;
	destination.h=source.h = height;

    destination.x = x;
    destination.y = y;

    //SDL_SetTextureAlphaMod(m_textureMap[imageId], alpha);
    SDL_RenderCopyEx(renderer, textureMap[imageId], &source, &destination, angle, 0, flip);

}

void 
TextureManager::clearTextureMap()
{
	map<string, SDL_Texture*>::iterator it;

	for(it = textureMap.begin(); it != textureMap.end() ;it++)
		SDL_DestroyTexture(it->second);

	textureMap.clear();
	textureCount.clear();
}

void 
TextureManager::clearFromTextureMap(string imageId)
{
	if(textureCount[imageId]==1)
	{
		SDL_DestroyTexture(textureMap[imageId]);
		textureMap.erase(imageId);
	}
	else
		textureCount[imageId]--;	
}

SDL_Texture* 
TextureManager::getTexture(string imageId)
{
	if(textureMap.find(imageId) == textureMap.end())
	{
		cout<<"Couldn't find the respective image with id: "<<imageId<<endl;
		return NULL;
	}
	else
		return textureMap[imageId];
}