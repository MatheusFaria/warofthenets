#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "SDL2/SDL.h"
#include "render.h"

class RenderableObject{
public:
	RenderableObject(Render *);
	~RenderableObject();

	SDL_Texture * getTexture();
	int getWidth();
	int getHeight();
	void setRender(Render *);

	void update();

protected:
	SDL_Renderer * getRenderer() const;
	virtual SDL_Texture * generateTexture() = 0;

private:
	Render * render;
	SDL_Texture * texture;
	int width;
	int height;
	
	static const int UNDEFINED_WIDTH_VALUE;
	static const int UNDEFINED_HEIGHT_VALUE;
};

#endif
