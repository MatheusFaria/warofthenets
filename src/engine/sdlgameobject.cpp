#include "sdlgameobject.h"
#include "texturemanager.h"
#include "render.h"

SDLGameObject::SDLGameObject(LoaderParams* params):GameObject(params)
{
	x = params->getX();
	y = params->getY();
	width = params->getWidth();
	height = params->getHeight();
	imageId = params->getImageId();

	currentRow = 1;
	currentFrame  = 1;
}

void
SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(imageId, x, y, currentRow, currentFrame,
	 Render::getInstance()->getRenderer(), 0);
}

	