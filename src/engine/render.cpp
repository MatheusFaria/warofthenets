#include "render.h"
#include "log.h"

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
		Log::warn("Failed to create Render");
	
	return this->renderer;
}

SDL_Renderer * 
Render::createRender(SDL_Surface * surface)
{
	this->renderer = SDL_CreateSoftwareRenderer(surface);

	if(this->renderer == NULL)
		Log::warn("Failed to create Render");

	return this->renderer;
}

void
Render::renderTexture(SDL_Texture * texture, int x, int y)
{
	if(texture == NULL)
	{
		Log::warn("Tried to render a NULL Texture");
		return;
	}
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(this->renderer, texture, NULL, &dst);
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

void 
Render::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;

	SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g,
									this->color.b, this->color.a);
}

