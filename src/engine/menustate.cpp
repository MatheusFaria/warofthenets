#include "menustate.h"
#include "playstate.h"
#include "inputhandler.h"
#include "render.h"
#include "texturemanager.h"
#include "LoaderParams.h"
#include "menubutton.h"
#include "game.h"
#include "SDL2/SDL.h"
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
	else
		std::cout<<"Okay"<<std::endl;	

	createMenu();
	
	
	std::cout<<"Entering Menu State"<<std::endl;

	return true;
}

void 
MenuState::createMenu()
{
	int width, height;

	//TextureManager::Instance()->drawFrame("playbutton", 0, 0, 1280,
	 //700, 0, 0, Render::getInstance()->getRenderer(), 0);

	SDL_QueryTexture(TextureManager::Instance()->getTexture("playbutton"), NULL, NULL,
		 &width, &height);

	//std::cout<<width<<" "<<height<<std::endl;

	int playx = (Game::Instance()->getWindow()->getWidth() / 2) - (width / 2);
	int playy= (Game::Instance()->getWindow()->getHeight() / 2) - (height / 2);

	GameObject* playButton = new MenuButton(new LoaderParams(playx, playy, 321, 179, "playbutton"), 
		menuToPlay);

	SDL_QueryTexture(TextureManager::Instance()->getTexture("exitbutton"), NULL, NULL,
		 &width, &height);

	int exitx = playx;
	int exity= playy + (Game::Instance()->getWindow()->getHeight() / 2)-playy + (height / 2);

	GameObject* exitButton = new MenuButton(new LoaderParams(exitx, exity, 307, 184, "exitbutton"), exitFromMenu);
	

	//TextureManager::Instance()->draw("fundo", 0,0, Render::getInstance()->getRenderer());
	menuObjects.push_back(playButton);
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
