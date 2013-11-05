#include "sdlgameobject.h"
#include "texturemanager.h"
#include "render.h"

SDLGameObject::SDLGameObject(int _x, int _y, int _width, int _height, string _imagePath, string _imageId,
	int _numFrames):GameObject() 
{
	this->position = Vector2D(_x, _y);
	width = _width;
	height=_height;
	imageId = _imageId;
	imagePath = _imagePath;

	currentRow = 0;
	currentFrame  = 0;
	numFrames = _numFrames;

	TextureManager::Instance()->loadImage(imagePath, 
		imageId, Render::getInstance()->getRenderer());

	SDL_QueryTexture(TextureManager::Instance()->getTexture(imageId), NULL, NULL,
		 &width, &height);
}

void
SDLGameObject::draw()
{
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width,
	 height/numFrames, currentRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

void
SDLGameObject::clean()
{
	TextureManager::Instance()->clearFromTextureMap(imageId);
}

void
SDLGameObject::update()
{
	
}
	
void
SDLGameObject::setPosition(int _x, int _y)
{
	this->position = Vector2D(_x, _y);
}

int
SDLGameObject::getWidth()
{
	return width;
}

int
SDLGameObject::getHeight()
{
	return height / numFrames;
}

Vector2D
SDLGameObject::getPosition()
{
    return position;
}


int
SDLGameObject::getX()
{
    return position.getX();
}

void
SDLGameObject::setX(int x)
{
    this->position = Vector2D(x, position.getY());
}

int
SDLGameObject::getY()
{
    return position.getY();
}

void
SDLGameObject::setY(int y)
{
    this->position = Vector2D(position.getX(), y);
}

void 
SDLGameObject::incCurrentRow()
{
	if(currentRow != numFrames)
		currentRow++;
}

void 
SDLGameObject::decCurrentRow()
{
	if(currentRow != 0)
		currentRow--;
}

int
SDLGameObject::getCurrentRow()
{
	return currentRow;
}





