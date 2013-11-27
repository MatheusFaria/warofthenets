#include "optionstate.h"
#include "game.h"
#include "inputhandler.h"
#include "texturemanager.h"
#include "soundmanager.h"

#include <iostream>

const std::string OptionState::optionId = "OPTION";

void
OptionState::update()
{
	for(int i = 0; i < (int)vectorGameObjects.size(); i++)
		vectorGameObjects[i]->update();
}

void
OptionState::render()
{
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
	SDL_RenderFillRect(rend, &rectBackground);
	
	if(SoundManager::Instance()->isEnable())
	    disableAudio->draw();
    else
        enableAudio->draw();
    
    //option->draw();
    int optionsX = (Game::Instance()->getWindow()->getWidth() / 2) - 195;
    TextureManager::Instance()->draw("options", optionsX, 10, 
		Render::getInstance()->getRenderer());
}

bool
OptionState::onEnter()
{    
	enableAudio = new MenuButton(0, 0, "resources/img/enablesound.png", "enablesound", 3, true);
	int enableAudioX = (Game::Instance()->getWindow()->getWidth() / 2) - (enableAudio->getWidth() / 2);
	int enableAudioY = (Game::Instance()->getWindow()->getHeight() / 2) - (enableAudio->getHeight() / 2);
	enableAudio->setPosition(enableAudioX, enableAudioY);
	enableAudio->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(enableAudio);
		
	
	disableAudio = new MenuButton(0, 0, "resources/img/disablesound.png", "disablesound", 3, true);
	disableAudio->setPosition(enableAudioX, enableAudioY);
	disableAudio->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(disableAudio);
	
	
	Image *option = new Image("resources/img/options.png", enableAudioX, 10);
	
	if(!TextureManager::Instance()->loadImage("resources/img/options.png",
		"options", Render::getInstance()->getRenderer()))
	{
		std::cout<<"Error"<<std::endl;
		return false;
	}
	
	vectorGameObjects.push_back(enableAudio);
	vectorGameObjects.push_back(disableAudio);
	vectorGameObjects.push_back(option);
	
	InputHandler::getInstance()->addKeyboardEvent(this);
	
    soundEnable = true;
    
    if(SoundManager::Instance()->isEnable())
        enableAudio->setActive(false);
    else
        disableAudio->setActive(false);
    
    rend = Game::Instance()->getWindow()->getRender()->getRenderer();
    rectBackground = {0, 0, 1280, 700};

	return true;
}

bool 
OptionState::onExit()
{
	for(int i = 0; i < (int)vectorGameObjects.size(); i++)
	{
		vectorGameObjects[i]->clean();
	    delete vectorGameObjects[i];
	}

	vectorGameObjects.clear();

	InputHandler::getInstance()->removeMouseClick(enableAudio);
	InputHandler::getInstance()->removeMouseClick(disableAudio);
	
	InputHandler::getInstance()->removeKeyboardEvent(this);

	return true;
}

std::string 
OptionState::getStateId() const
{
	return optionId;
}

bool 
OptionState::eventInMe(SDL_Event sdlEvent)
{
    if(sdlEvent.key.keysym.sym == SDLK_ESCAPE){
		Game::Instance()->getStateMachine()->popState();
		return true;
	}

	return false;
}

void
OptionState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == enableAudio)
    {
        SoundManager::Instance()->setEnable(true);
        enableAudio->setActive(false);
        disableAudio->setActive(true);
    }
    
    if(mouseClick == disableAudio)
    {
        SoundManager::Instance()->setEnable(false);
        SoundManager::Instance()->stopSound();
        disableAudio->setActive(false);
        enableAudio->setActive(true);
    }
}

