#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "SDL2/SDL.h"
#include "render.h"

class DrawableObject{
public:
	DrawableObject();
	~DrawableObject();

	SDL_Texture * getTexture();
	SDL_Texture * generateTexture(SDL_Renderer *);
	
	void init();
	//virtual void draw() = 0;


protected:
	Render * render;
	SDL_Texture * texture;
	int width;
	int height;

private:
	SDL_Surface * surface;
	Uint32 rmask;
	Uint32 gmask;
	Uint32 bmask;
	Uint32 amask;
	Uint32 flags;
	int bpp;

	void generateDrawSurface();
	void generateDrawRender();
	void paintTransparentSurface();
};

#endif
