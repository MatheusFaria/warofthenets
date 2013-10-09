#include "drawableobject.h"
#include "log.h"

DrawableObject::DrawableObject(int w, int h, int posX, int posY) 
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

	this->surface = NULL;
	this->texture = NULL;
	render = NULL;

	width = w;
	height = h;
	x = posX;
	y = posY;
}

DrawableObject::~DrawableObject()
{
	if(render != NULL)
		delete render;
	if(this->surface != NULL)
		SDL_FreeSurface(this->surface);
	if(this->texture != NULL)
		SDL_DestroyTexture(this->texture);
}

void 
DrawableObject::init()
{
	this->generateDrawSurface();
	this->generateDrawRender();
}

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
DrawableObject::draw()
{
	eraseDraw();
	putObjectInSurface();
	render->present();
}

void
DrawableObject::eraseDraw()
{
	SDL_Color actualColor = render->getColor();
	SDL_Color transparentBlack = {0, 0, 0, 0};

	setDrawColor(transparentBlack.r, transparentBlack.g,
							transparentBlack.b, transparentBlack.a);
	render->clear();
	render->present();
	
	setDrawColor(actualColor.r, actualColor.g,
					actualColor.b, actualColor.a);
}


void 
DrawableObject::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	render->setColor(r, g, b, a);
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

int
DrawableObject::getWidth()
{
    return this->width;
}

int
DrawableObject::getHeight()
{
    return this->height;
}

int
DrawableObject::getX()
{
    return this->x;
}

int
DrawableObject::getY()
{
    return this->y;
}

