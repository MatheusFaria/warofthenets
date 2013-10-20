#include "menustate.h"
#include "playstate.h"
#include "inputhandler.h"
#include "render.h"
#include "texturemanager.h"
#include "game.h"
#include "text.h"
#include "SDL2/SDL.h"
#include "soundmanager.h"
#include <iostream>

const std::string MenuState::menuId = "MENU";

void
MenuState::update()
{
	TextureManager::Instance()->drawFrame("fundo", 0, 0, 1280,
	 700, 0, 0, Render::getInstance()->getRenderer(), 0);

	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->update();
}

void
MenuState::render()
{
	//std::cout<<"Drawing menu"<<std::endl;

	TextureManager::Instance()->drawFrame("fundo", 0, 0, 1280,
	 700, 0, 0, Render::getInstance()->getRenderer(), 0);

	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->draw();
}

bool
MenuState::onEnter()
{
	/*
	if(!TextureManager::Instance()->loadImage("resources/img/play.png", 
		"playbutton", Render::getInstance()->getRenderer()))
	{
		return false;	
	}

	if(!TextureManager::Instance()->loadImage("resources/img/about.png",
		"aboutbutton", Render::getInstance()->getRenderer()))
	{
		return false;
	}

	if(!TextureManager::Instance()->loadImage("resources/img/exit.png",
		"exitbutton", Render::getInstance()->getRenderer()))
	{
		return false;
	}
	*/
	if(!TextureManager::Instance()->loadImage("resources/img/fundo.png",
		"fundo", Render::getInstance()->getRenderer()))
	{
		std::cout<<"Error"<<std::endl;
		return false;
	}
	
	
	createMenu();
	
	std::cout<<"Entering Menu State"<<std::endl;

	return true;
}

void 
MenuState::createMenu()
{
	/*
	int width, height;

	SDL_QueryTexture(TextureManager::Instance()->getTexture("playbutton"), NULL, NULL,
		 &width, &height);
	*/

	

	playButton = new MenuButton(0, 0, "resources/img/play.png", "playbutton");
	int playx = (Game::Instance()->getWindow()->getWidth() / 2) - (playButton->getWidth() / 2);
	int playy= (Game::Instance()->getWindow()->getHeight() / 2) - (playButton->getHeight() / 2);
	playButton->setPosition(playx, playy);
	playButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(playButton);
	
	/*
	SDL_QueryTexture(TextureManager::Instance()->getTexture("aboutbutton"), NULL, NULL,
		 &width, &height);
	*/

	
	aboutButton = new MenuButton(0, 0, "resources/img/about.png", "aboutbutton");
	int aboutx = playx;
	int abouty= playy + (Game::Instance()->getWindow()->getHeight() / 2)-playy + (aboutButton->getHeight() / 2);
	aboutButton->setPosition(aboutx, abouty);
	aboutButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(aboutButton);
	
	/*
	SDL_QueryTexture(TextureManager::Instance()->getTexture("exitbutton"), NULL, NULL, 
		&width, &height);
	*/

	

	//std::cout<<Game::Instance()->getWindow()->getHeight()<<std::endl;

	exitButton = new MenuButton(0, 0, "resources/img/exit.png", "exitbutton");
	int exitx = (Game::Instance()->getWindow()->getWidth() / 4) - (exitButton->getWidth());
	int exity = (Game::Instance()->getWindow()->getHeight()) - exitButton->getHeight() - 10;
	exitButton->setPosition(exitx, exity);
	exitButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(exitButton);

	menuObjects.push_back(playButton);
	menuObjects.push_back(aboutButton);
	menuObjects.push_back(exitButton);

}

bool 
MenuState::onExit()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->clean();

	menuObjects.clear();

	/*
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	TextureManager::Instance()->clearFromTextureMap("fundo");
	*/
	SoundManager::Instance()->clearFromSoundManager("theme", MUSIC);
	
	InputHandler::getInstance()->removeMouseClick(playButton);
	InputHandler::getInstance()->removeMouseClick(aboutButton);
	InputHandler::getInstance()->removeMouseClick(exitButton);

	return true;
}

std::string 
MenuState::getStateId() const
{
	return menuId;
}

void
MenuState::menuToPlay()
{
	Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void
MenuState::exitFromMenu()
{
	std::cout<<"Exit button touched"<<std::endl;
}

void
MenuState::onMouseClick(MouseClick *mouseClick)
{
    
    if(mouseClick == playButton)
        menuToPlay();
    
    if(mouseClick == aboutButton)
        std::cout<<"About button touched"<<std::endl;
        
    if(mouseClick == exitButton)
        exitFromMenu();
    
}


























