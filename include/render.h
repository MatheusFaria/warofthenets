#ifndef RENDER_H
#define RENDER_H

#include "SDL2/SDL.h"

class Render{
public:
	Render();
	~Render();
	
	SDL_Renderer * createRender(SDL_Window *);
	
	void renderAll();
	void renderTexture(SDL_Texture *, int, int);
	
	void clear();
	void present();
	
	static Render * getInstance();
	
	SDL_Renderer * getRenderer();
	
private:
	SDL_Renderer * renderer;
	static Render* instance;
	
};

#endif
