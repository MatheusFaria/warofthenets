#include "game.h"
#include "pausestate.h"
#include "menustate.h"
#include <iostream>

const std::string PauseState::pauseId = "PAUSE";

void 
PauseState::toMenu()
{
	Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void 
PauseState::backToGame()
{
	Game::Instance()->getStateMachine()->popState();
}


void
PauseState::update()
{
	for(int i =0; i<(int)pauseObjects.size(); i++)
		pauseObjects[i]->update();
}

void
PauseState::render()
{
	for(int i =0; i<(int)pauseObjects.size(); i++)
		pauseObjects[i]->draw();
}

bool
PauseState::onEnter()
{
	return true;
}

bool
PauseState::onExit()
{
	return true;
}

std::string 
PauseState::getStateId()
{
	return pauseId;
}
