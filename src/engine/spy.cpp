#include "spy.h"
#include "SDL2/SDL.h"
#include "texturemanager.h"
#include "render.h"
#include <iostream>

std::string Spy::path = "resources/img/spy.png";

Spy::Spy(int numLevelSpy, int x, int y):Image(path,x,y)
{
	this->numLevelSpy = numLevelSpy;
	currentFrame = numLevelSpy - 1;
}

void
Spy::update()
{

}

void
Spy::draw()
{
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width,
	 height, currentRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

int
Spy::getLevel()
{
	return numLevelSpy;
}