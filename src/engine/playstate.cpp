#include "playstate.h"

const std::string PlayState::playId = "PLAY";

void
PlayState::update()
{

}

void
PlayState::render()
{

}

bool
PlayState::onEnter()
{
	return true;
}

bool 
PlayState::onExit()
{
	return true;
}

std::string 
PlayState::getStateId() const
{
	return playId;
}