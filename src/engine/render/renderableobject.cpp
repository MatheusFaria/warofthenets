#include "renderableobject.h"

const int RenderableObject::UNDEFINED_WIDTH_VALUE = -1;
const int RenderableObject::UNDEFINED_HEIGHT_VALUE = -1;

RenderableObject::RenderableObject(Render * render)
{
	this->render = render;
	this->texture = NULL;
	this->width = UNDEFINED_WIDTH_VALUE;
	this->height = UNDEFINED_HEIGHT_VALUE;
}

RenderableObject::~RenderableObject()
{
	if(this->texture != NULL)
		SDL_DestroyTexture(this->texture);
}

void
RenderableObject::update()
{
	this->texture = generateTexture();
}

SDL_Texture * 
RenderableObject::getTexture()
{
	if(this->texture == NULL)
		this->texture = generateTexture();
	return this->texture;
}

int 
RenderableObject::getWidth()
{
	if(this->width == UNDEFINED_WIDTH_VALUE && this->texture != NULL)
		SDL_QueryTexture(texture, NULL, NULL, &(this->width), NULL);
	return this->width;
}

int
RenderableObject::getHeight()
{
	if(this->height == UNDEFINED_HEIGHT_VALUE && this->texture != NULL)
		SDL_QueryTexture(texture, NULL, NULL, NULL, &(this->height));
	return this->height;
}

void 
RenderableObject::setRender(Render * render)
{
	this->render = render;
}

SDL_Renderer * 
RenderableObject::getRenderer() const
{
	if(this->render == NULL)
		return NULL;
	return this->render->getRenderer();
}
