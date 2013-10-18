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
	int width, height;

	SDL_QueryTexture(TextureManager::Instance()->getTexture("playbutton"), NULL, NULL,
		 &width, &height);


	int playx = (Game::Instance()->getWindow()->getWidth() / 2) - (width / 2);
	int playy= (Game::Instance()->getWindow()->getHeight() / 2) - (height / 2);

	GameObject* playButton = new MenuButton(playx, playy, 321, 179, "playbutton", menuToPlay);

	SDL_QueryTexture(TextureManager::Instance()->getTexture("aboutbutton"), NULL, NULL,
		 &width, &height);

	int aboutx = playx;
	int abouty= playy + (Game::Instance()->getWindow()->getHeight() / 2)-playy + (height / 2);

	GameObject* aboutButton = new MenuButton(aboutx, abouty, 325, 191, "aboutbutton", exitFromMenu);

	SDL_QueryTexture(TextureManager::Instance()->getTexture("exitbutton"), NULL, NULL, 
		&width, &height);

	int exitx = (Game::Instance()->getWindow()->getWidth() / 4) - (width);
	int exity = (Game::Instance()->getWindow()->getHeight()) - height - 10;

	std::cout<<Game::Instance()->getWindow()->getHeight()<<std::endl;

	GameObject* exitButton = new MenuButton(exitx, exity, 307, 184, "exitbutton", exitFromMenu);

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

	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	TextureManager::Instance()->clearFromTextureMap("fundo");
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
