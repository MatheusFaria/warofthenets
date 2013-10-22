#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "SDL2/SDL.h"
#include "render.h"

class RenderableObject{
public:
	RenderableObject(Render *);
	RenderableObject(Render *, int, int, int);
	~RenderableObject();

	SDL_Texture * getTexture();
	int getWidth();
	int getHeight();
	void setRender(Render *);

	int getNumberSprites() const;
	int getSpritesLines() const;
	int getSpritesColumns() const;
	SDL_Renderer * getRenderer() const;

	void update();

protected:
	virtual SDL_Texture * generateTexture() = 0;

private:
	Render * render;
	SDL_Texture * texture;
	int width;
	int height;
	int sprites;
	int spritesLines;
	int spritesCols;
	
	static const int UNDEFINED_WIDTH_VALUE;
	static const int UNDEFINED_HEIGHT_VALUE;
};

#endif
