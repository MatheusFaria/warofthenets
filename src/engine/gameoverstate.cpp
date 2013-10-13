#include "gameoverstate.h"
#include <iostream>

const std::string GameOverState::gameOverId = "GAMEOVER";

void
GameOverState::update()
{
	for(int i =0; i<(int)gameOverObjects.size(); i++)
		gameOverObjects[i]->update();
}

void
GameOverState::render()
{
	for(int i =0; i<(int)gameOverObjects.size(); i++)
		gameOverObjects[i]->draw();
}

bool
GameOverState::onEnter()
{
	std::cout<<"Entering Game Over State"<<std::endl;
	return true;
}

bool
GameOverState::onExit()
{
	std::cout<<"Exiting Game Over State"<<std::endl;
	return true;
}

std::string 
GameOverState::getGameOverId() const
{
	return gameOverId;
}