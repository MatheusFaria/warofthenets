#include "attractstate.h"
#include "menustate.h"
#include "game.h"
#include "soundmanager.h"
#include "texturemanager.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"
#include <cstdlib>

#include <iostream>
using namespace std;


const std::string AttractState::attractId = "ATTRACT";


void 
AttractState::update()
{
    
}


void
AttractState::render()
{
    imageAttract->draw();
}


bool
AttractState::onEnter()
{
    int x, y;

	imageAttract = new Image("resources/img/history.png");
    x = (Game::Instance()->getWindow()->getWidth() / 2) - (imageAttract->getWidth()/2);
    y = (Game::Instance()->getWindow()->getHeight() / 2) - (imageAttract->getHeight()/2);
    imageAttract->setPosition(x, y);
        
	//SoundManager::Instance()->loadSound("resources/audio/Credits_George_Street_Shuffle.ogg", "credit", MUSIC);
	//SoundManager::Instance()->playMusic("credit", -1);
    
	InputHandler::getInstance()->addEvent(this);
	

	return true;
}


bool 
AttractState::onExit()
{
    InputHandler::getInstance()->removeEvent(this);
    
    delete imageAttract;

	//SoundManager::Instance()->stopSound();
	//SoundManager::Instance()->clearFromSoundManager("theme", MUSIC);


	return true;
}


void 
AttractState::enable()
{
    this->setActive(true);
}

void 
AttractState::disable()
{
    this->setActive(false);
}


bool
AttractState::eventInMe(SDL_Event sdlEvent)
{
    if(verifyEvent(sdlEvent))
    {
        //InputHandler::getInstance()->removeEvent(this);
        Game::Instance()->getStateMachine()->popState();
        return true;
    }
    else
    {
        return false;
    }
}


bool 
AttractState::verifyEvent(SDL_Event sdlEvent)
{
    if(sdlEvent.type == SDL_MOUSEMOTION)
    {
        
        if( this->sdlEvent.motion.x == 0 &&
            this->sdlEvent.motion.y == 0)
        {
            SDL_Event temp = sdlEvent;
            this->sdlEvent = temp;
            return false;
        }
        
        if( abs(this->sdlEvent.motion.x - sdlEvent.motion.x) > 2 ||
            abs(this->sdlEvent.motion.y - sdlEvent.motion.y) > 2 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if( (sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP) ||
        (sdlEvent.type == SDL_KEYDOWN) ||
        (sdlEvent.type == SDL_KEYUP))
        return true;
    else
        return false;
}


std::string 
AttractState::getStateId() const
{
    return attractId;
}













