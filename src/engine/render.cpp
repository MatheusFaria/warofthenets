#include "render.h"

#include <iostream>
using namespace std;

Render *Render::instance = NULL;

Render::Render()
{
	
}

Render::~Render()
{
	if(this->renderer != NULL)
		SDL_DestroyRenderer(this->renderer);
}

SDL_Renderer * 
Render::createRender(SDL_Window * win)
{
	this->renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
	
	if(this->renderer == NULL)
		cout << "Failed to create Render" << endl;
	
	return this->renderer;
}

Render& 
Render::getInstance()
{
	if(instance == NULL)
		instance = new Render();
	return *instance;
}

	
void 
Render::renderAll()
{
	
}

void
Render::renderImage(Image img, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(img.getTexture(), NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(this->renderer, img.getTexture(), NULL, &dst);
}

void 
Render::clear()
{
	SDL_RenderClear(this->renderer);
}

void 
Render::present()
{
	SDL_RenderPresent(this->renderer);
}

SDL_Renderer * 
Render::getRenderer()
{
	return this->renderer;
}

