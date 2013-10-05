#ifndef RENDER_H
#define RENDER_H

#include "SDL2/SDL.h"

class Render{
public:
	Render();
	~Render();
	
	SDL_Renderer * createRender(SDL_Window *);
	SDL_Renderer * createRender(SDL_Surface *);

	void renderTexture(SDL_Texture *, int, int);
	
	void clear();
	void present();
	
	void setColor(Uint8, Uint8, Uint8, Uint8);
	SDL_Color getColor();
	SDL_Renderer * getRenderer();

private:
	SDL_Renderer * renderer;
	SDL_Color color;
};

#endif
