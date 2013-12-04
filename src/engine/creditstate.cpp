#include "creditstate.h"
#include "menustate.h"
#include "game.h"
#include "soundmanager.h"
#include "texturemanager.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"

#include <iostream>
using namespace std;

const std::string CreditState::creditId = "CREDIT";


void 
CreditState::update()
{
	if(imageY > -1500)
	    velocity = -1;
	    //velocity = -3.25;
	    //velocity = -0.1625;
    else
        velocity = 0;
    
    //imageY += ((SDL_GetTicks() - previousTime) / 100) * velocity;
    
    imageY += velocity;
    
    previousTime = SDL_GetTicks();
    
    cout << "\n\nimageY: " << imageY << endl;
    cout << "velocity: " << velocity << endl;

}

void 
CreditState::render()
{
	TextureManager::Instance()->draw(imageId, imageX, imageY, 
		Render::getInstance()->getRenderer());
	
	SDL_SetRenderDrawColor(Game::Instance()->getWindow()->getRender()->getRenderer(), 0, 0, 0, 0);
}

bool
CreditState::onEnter()
{
	imagePath = "resources/img/castscreen.png";
	imageId = "credit";

	SoundManager::Instance()->loadSound("resources/audio/Credits_George_Street_Shuffle.ogg", "credit", MUSIC);
	SoundManager::Instance()->playMusic("credit", -1);

	if(!TextureManager::Instance()->loadImage(imagePath,
	 imageId, Render::getInstance()->getRenderer()))
	{
		return false;
	}

	imageX = (Game::Instance()->getWindow()->getWidth() / 2) - 400;
	imageY = Game::Instance()->getWindow()->getHeight(); 
    
    previousTime = SDL_GetTicks();
    
	InputHandler::getInstance()->addKeyboardEvent(this);

	return true;
}

void 
CreditState::enable()
{
    this->setActive(true);
}

void 
CreditState::disable()
{
    this->setActive(false);
}

bool
CreditState::onExit()
{
	TextureManager::Instance()->clearFromTextureMap(imageId);
    
    InputHandler::getInstance()->removeKeyboardEvent(this);

    SoundManager::Instance()->clearFromSoundManager("credit", MUSIC);

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
		Game::Instance()->getStateMachine()->pushState(new MenuState());
		return true;
	}

	return false;
}
