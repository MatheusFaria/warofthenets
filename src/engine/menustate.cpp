#include "menustate.h"
#include "inputhandler.h"
#include "render.h"
#include "texturemanager.h"
#include "LoaderParams.h"
#include "menubutton.h"
#include <iostream>

const std::string MenuState::menuId = "MENU";

void
MenuState::update()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->update();
}

void
MenuState::render()
{
	//std::cout<<"Drawing menu"<<std::endl;

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

	/*if(!TextureManager::Instance()->loadImage("resources/img/fundo.jpg",
	 	"fundo", Render::getInstance()->getRenderer()));
	{
		std::cout<<"Ferrou"<<std::endl;
		return false;
	}*/

	GameObject* playButton = new MenuButton(new LoaderParams(490, 400, 321, 179, "playbutton"), menuToPlay);	
	GameObject* exitButton = new MenuButton(new LoaderParams(490, 629, 307, 184, "exitbutton"), exitFromMenu);

	//TextureManager::Instance()->draw("fundo", 0,0, Render::getInstance()->getRenderer());
	menuObjects.push_back(playButton);
	menuObjects.push_back(exitButton);

	
	std::cout<<"Entering Menu State"<<std::endl;

	return true;
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
	std::cout<<"Played button touched"<<std::endl;
}

void
MenuState::exitFromMenu()
{
	std::cout<<"Exit button touched"<<std::endl;
}
