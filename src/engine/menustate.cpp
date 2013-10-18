#include "menustate.h"
#include "playstate.h"
#include "inputhandler.h"
#include "render.h"
#include "texturemanager.h"
#include "menubutton.h"
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

	

	MenuButton* playButton = new MenuButton(0, 0, "resources/img/play.png", "playbutton", menuToPlay);
	int playx = (Game::Instance()->getWindow()->getWidth() / 2) - (playButton->getWidth() / 2);
	int playy= (Game::Instance()->getWindow()->getHeight() / 2) - (playButton->getHeight() / 2);
	playButton->setPosition(playx, playy);

	/*
	SDL_QueryTexture(TextureManager::Instance()->getTexture("aboutbutton"), NULL, NULL,
		 &width, &height);
	*/

	
	MenuButton* aboutButton = new MenuButton(0, 0, "resources/img/about.png", "aboutbutton", exitFromMenu);
	int aboutx = playx;
	int abouty= playy + (Game::Instance()->getWindow()->getHeight() / 2)-playy + (aboutButton->getHeight() / 2);
	aboutButton->setPosition(aboutx, abouty);
	/*
	SDL_QueryTexture(TextureManager::Instance()->getTexture("exitbutton"), NULL, NULL, 
		&width, &height);
	*/

	

	//std::cout<<Game::Instance()->getWindow()->getHeight()<<std::endl;

	MenuButton* exitButton = new MenuButton(0, 0, "resources/img/exit.png", "exitbutton", exitFromMenu);
	int exitx = (Game::Instance()->getWindow()->getWidth() / 4) - (exitButton->getWidth());
	int exity = (Game::Instance()->getWindow()->getHeight()) - exitButton->getHeight() - 10;
	exitButton->setPosition(exitx, exity);

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
