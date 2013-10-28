#include "creditstate.h"
#include "game.h"
#include "texturemanager.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"
#include <iostream>


const std::string CreditState::creditId = "CREDIT";

void 
CreditState::update()
{
	if(imageY>0)
		imageY -= ((SDL_GetTicks() / 100) % Game::Instance()->getWindow()->getHeight()/4);

}

void 
CreditState::render()
{
	TextureManager::Instance()->draw(imageId, imageX, imageY, 
		Render::getInstance()->getRenderer());
}

bool
CreditState::onEnter()
{
	imagePath = "resources/img/credits.png";
	imageId = "credit";
	if(!TextureManager::Instance()->loadImage(imagePath,
	 imageId, Render::getInstance()->getRenderer()))
	{
		return false;
	}

	imageX = (Game::Instance()->getWindow()->getWidth() / 2) - 400;
	imageY = Game::Instance()->getWindow()->getHeight(); 

	velocity = 0.1;

	InputHandler::getInstance()->addKeyboardEvent(this);

	return true;
}

bool
CreditState::onExit()
{
	TextureManager::Instance()->clearFromTextureMap(imageId);

	return true;
}

std::string 
CreditState::getStateId() const
{
	return creditId;
}

bool 
CreditState::eventInMe(SDL_Event sdlEvent)
{
	if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
		Game::Instance()->getStateMachine()->popState();
		return true;
	}

	return false;
}
