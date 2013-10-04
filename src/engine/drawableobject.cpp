#include "drawableobject.h"
#include "log.h"

DrawableObject::DrawableObject() 
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	this->rmask = 0xff000000;
	this->gmask = 0x00ff0000;
	this->bmask = 0x0000ff00;
	this->amask = 0x000000ff;
#else
	this->rmask = 0x000000ff;
	this->gmask = 0x0000ff00;
	this->bmask = 0x00ff0000;
	this->amask = 0xff000000;
#endif

	this->flags = 0;
	this->bpp = 32;
}

DrawableObject::~DrawableObject() {}

SDL_Texture * 
DrawableObject::getTexture()
{
	return texture;
}

SDL_Texture * 
DrawableObject::generateTexture(SDL_Renderer * outsideRender)
{
	texture = SDL_CreateTextureFromSurface(outsideRender, this->surface);
	return texture;
}

void
DrawableObject::init()
{
	this->generateDrawSurface();
	this->generateDrawRender();
	this->paintTransparentSurface();
}

void
DrawableObject::generateDrawSurface()
{
	this->surface = SDL_CreateRGBSurface(this->flags, width, height, this->bpp,
								   this->rmask, this->gmask, this->bmask, this->amask);
}

void
DrawableObject::generateDrawRender()
{
	render = new Render(); 
	render->createRender(this->surface);
}

void
DrawableObject::paintTransparentSurface()
{
	SDL_Color transparentBlack = {0, 0, 0, 0};
	render->setColor(transparentBlack.r, transparentBlack.g,
							transparentBlack.b, transparentBlack.a);
	render->clear();
	render->present();
}
	
