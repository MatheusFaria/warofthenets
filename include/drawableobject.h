#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "SDL2/SDL.h"
#include "renderableobject.h"

class DrawableObject: public RenderableObject {
public:
	DrawableObject(Render *);
	DrawableObject(Render *, int, int);
	~DrawableObject();

	void draw();
	void eraseDraw();
	void setDrawColor(Uint8, Uint8, Uint8, Uint8=255);
	
protected:
	virtual void putObjectInSurface() = 0;
	SDL_Texture * generateTexture();

	SDL_Renderer * getInternalRenderer();
	int getSurfaceWidth();
	int getSurfaceHeight();
	void setSurfaceHeight(int);
	void setSurfaceWidth(int);

private:
	SDL_Renderer * internalRenderer;
	SDL_Surface * surface;
	SDL_Color color;

	int surfaceWidth;
	int surfaceHeight;

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
