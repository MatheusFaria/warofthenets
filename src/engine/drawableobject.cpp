#include "drawableobject.h"
#include "render.h"
#include "log.h"

DrawableObject::DrawableObject(Render * render, int w, int h, int x, int y) 
:RenderableObject(render)
{
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		this->rmask = 0xff000000;
		this->gmask = 0x00ff0000;
		this->bmask = 0x0000ff00;
		this->amask = 0x000000ff;
	}
	else
	{
		this->rmask = 0x000000ff;
		this->gmask = 0x0000ff00;
		this->bmask = 0x00ff0000;
		this->amask = 0xff000000;
	}

	this->flags = 0;
	this->bpp = 32;

	this->surface = NULL;
	this->internalRenderer = NULL;

	this->surfaceWidth = w;
	this->surfaceHeight = h;

	this->setX(x);
	this->setY(y);
}

DrawableObject::~DrawableObject()
{
	if(this->surface != NULL)
		SDL_FreeSurface(this->surface);
	if(this->internalRenderer != NULL)
		SDL_DestroyRenderer(this->internalRenderer);
}

SDL_Texture * 
DrawableObject::generateTexture()
{
	canvas();
	return SDL_CreateTextureFromSurface(getRenderer(), this->surface);
}

void
DrawableObject::canvas()
{
	
	if(this->surface == NULL)
		this->generateDrawSurface();
	if(this->internalRenderer == NULL)
		this->generateDrawRender();
	eraseDraw();
	putObjectInSurface();
	SDL_RenderPresent(this->internalRenderer);
	
	
}

void 
DrawableObject::draw()
{
	Render::getInstance()->renderTexture(getTexture(), getX(), getY());
}

void
DrawableObject::eraseDraw()
{
	SDL_Color actualColor = this->color;
	SDL_Color transparentBlack = {0, 0, 0, 0};

	SDL_SetRenderDrawColor(this->internalRenderer, transparentBlack.r, transparentBlack.g,
									transparentBlack.b, transparentBlack.a);

	//setDrawColor(transparentBlack.r, transparentBlack.g,
	//						transparentBlack.b, transparentBlack.a);
	SDL_RenderClear(this->internalRenderer);
	SDL_RenderPresent(this->internalRenderer);

	SDL_SetRenderDrawColor(this->internalRenderer, actualColor.r, actualColor.g,
									actualColor.b, actualColor.a);
	
	//setDrawColor(actualColor.r, actualColor.g,
	//				actualColor.b, actualColor.a);
}


void 
DrawableObject::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	if(this->color.r == r && this->color.g == g && 
		 this->color.b ==b && this->color.a == a)
		return;

	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
	SDL_SetRenderDrawColor(this->internalRenderer, this->color.r, this->color.g,
									this->color.b, this->color.a);

	updateTexture();
}

void
DrawableObject::generateDrawSurface()
{
	this->surface = SDL_CreateRGBSurface(this->flags, this->surfaceWidth, this->surfaceHeight, this->bpp,
								   this->rmask, this->gmask, this->bmask, this->amask);
}

void
DrawableObject::generateDrawRender()
{
	this->internalRenderer = SDL_CreateSoftwareRenderer(this->surface); 
}

void
DrawableObject::setSurfaceWidth(int w)
{
	this->surfaceWidth = w;
}

void
DrawableObject::setSurfaceHeight(int h)
{
	this->surfaceHeight = h;
}

int
DrawableObject::getSurfaceWidth()
{
	return this->surfaceWidth;
}

int
DrawableObject::getSurfaceHeight()
{
	return this->surfaceHeight;
}

SDL_Renderer *
DrawableObject::getInternalRenderer()
{
	return this->internalRenderer;
}


Vector2D 
DrawableObject::getPosition()
{
	return position;
}

void 
DrawableObject::setPosition(int x, int y)
{
	position.setX(x);
	position.setY(y);
}


int 
DrawableObject::getX()
{
	return position.getX();
}

void 
DrawableObject::setX(int x)
{
	position.setX(x);
}


int 
DrawableObject::getY()
{
	return position.getY();
}

void 
DrawableObject::setY(int y)
{
	position.setY(y);
}


