#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "SDL2/SDL.h"
#include "vector2d.h"
#include "renderableobject.h"

class DrawableObject: public RenderableObject {
public:
	DrawableObject(Render *, int = 0, int = 0, int = 0, int = 0);
	~DrawableObject();

	//void draw();
	void draw();
	void canvas();
	void eraseDraw();
	void setDrawColor(Uint8, Uint8, Uint8, Uint8=255);

	Vector2D getPosition();
	void setPosition(int x, int y);

	int getX();
	void setX(int x);

	int getY();
	void setY(int y);
	
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

	Vector2D position;

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
