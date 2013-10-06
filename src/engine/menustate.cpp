#include "menustate.h"
#include "inputhandler.h"
#include "vector2d.h"

const std::string MenuState::menuId = "MENU";

void
MenuState::update()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i].update();
}

void
MenuState::render()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i].render();
}

bool
MenuState::onEnter()
{
	return true;
}

bool 
MenuState::onExit()
{
	return true;
}

std::string 
MenuState::getStateId()
{
	return menuId;
}