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
	std::cout<<"Drawing menu"<<std::endl;

	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->draw();
}

bool
MenuState::onEnter()
{

	if(!TextureManager::Instance()->loadImage("/home/lucas/warofthenets/resources/img/button.png", 
		"playbutton", Render::getInstance()->getRenderer()))
	{
		return false;	
	}

	if(!TextureManager::Instance()->loadImage("/home/lucas/warofthenets/resources/img/exit.png",
		"exitbutton", Render::getInstance()->getRenderer()))
	{
		return false;
	}

	GameObject* playButton = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"));	
	GameObject* exitButton = new MenuButton(new LoaderParams(100, 500, 400, 100, "exitbutton"));

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

	return true;
}

std::string 
MenuState::getStateId() const
{
	return menuId;
}