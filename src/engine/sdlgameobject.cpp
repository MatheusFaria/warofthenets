#include "sdlgameobject.h"
#include "texturemanager.h"
#include "render.h"

SDLGameObject::SDLGameObject(int _x, int _y, int _width, int _height, string _imageId):GameObject() 
{
	this->position = Vector2D(_x, _y);
	width = _width;
	height=_height;
	imageId = _imageId;

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
	
