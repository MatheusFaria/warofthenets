#include "playstate.h"
#include <iostream>

const std::string PlayState::playId = "PLAY";

void
PlayState::update()
{
	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->update();
}

void
PlayState::render()
{
	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->draw();
}

bool
PlayState::onEnter()
{
	std::cout<<"Play State"<<std::endl;
	return true;
}

bool 
PlayState::onExit()
{
	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->clean();

	return true;
}

std::string 
PlayState::getStateId() const
{
	return playId;
}