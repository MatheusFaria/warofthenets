#include "torre.h"
#include "SDL2/SDL.h"
#include "texturemanager.h"
#include "render.h"
#include <iostream>

std::string Torre::path = "resources/img/tower.png";

Torre::Torre(int x, int y):Image(path,x,y)
{
	numFrames = 4;
	actualRow = 1;
}

void
Torre::update()
{
	int intervalo = 100;

	//actualRow++;

	//actualRow = (actualRow % 4) + 1;

	actualRow = (SDL_GetTicks()/intervalo)%numFrames;

	//TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),
		//width,height/4, actualRow, 1,Render::getInstance()->getRenderer(), 0);
}

void
Torre::draw()
{
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width,
	 height/4, actualRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}