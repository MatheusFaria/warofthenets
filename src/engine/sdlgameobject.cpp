#include "sdlgameobject.h"
#include "texturemanager.h"
#include "render.h"

SDLGameObject::SDLGameObject(LoaderParams* params):GameObject(params) 
{
	width = params->getWidth();
	height = params->getHeight();
	imageId = params->getImageId();
	this->position = Vector2D(params->getX(), params->getY());

	currentRow = 1;
	currentFrame  = 1;
}

void
SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(imageId, position.getX(),position.getY(), currentRow, currentFrame,
	 Render::getInstance()->getRenderer(), 0);
}

	