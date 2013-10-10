#include "sdlgameobject.h"
#include "texturemanager.h"
#include "render.h"

SDLGameObject::SDLGameObject(LoaderParams* params):GameObject(params) 
{
	width = params->getWidth();
	height = params->getHeight();
	imageId = params->getImageId();
	this->position = Vector2D(params->getX(), params->getY());

	currentRow = 0;
	currentFrame  = 0;
}

void
SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width,
	 height, currentRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

void
SDLGameObject::clean()
{

}

void
SDLGameObject::update()
{
	
}
	