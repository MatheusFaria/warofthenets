#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "SDL2/SDL.h"
#include "render.h"

#define MIN_HEIGHT 1
#define MIN_WIDTH  1

class DrawableObject{
public:
	DrawableObject(int, int, int = 0, int = 0);
	~DrawableObject();

	void init();

	SDL_Texture * getTexture();
	SDL_Texture * generateTexture(SDL_Renderer *);
	
	void draw();
	void eraseDraw();
	void setDrawColor(Uint8, Uint8, Uint8, Uint8=255);
	
	int getWidth();
	int getHeight();
	int getX();
	int getY();

protected:
	Render * render;
	int width;
	int height;
	int x;
	int y;

	virtual void putObjectInSurface() = 0;

private:
	SDL_Surface * surface;
	SDL_Texture * texture;
	Uint32 rmask;
	Uint32 gmask;
	Uint32 bmask;
	Uint32 amask;
	Uint32 flags;
	int bpp;

	void generateDrawSurface();
	void generateDrawRender();
};

#endif
