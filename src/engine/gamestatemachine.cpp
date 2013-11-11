#include "gamestatemachine.h"
#include <iostream>

void
GameStateMachine::update()
{
	if(!gameStates.empty())
		gameStates.back()->update();
}

void
GameStateMachine::render()
{
	if(!gameStates.empty())
		gameStates.back()->render();
}

void
GameStateMachine::clean()
{
	if(!gameStates.empty())
	{
		delete gameStates.back();
		gameStates.clear();
	}
}

void
GameStateMachine::pushState(GameState* state)
{
	if( (state != NULL) && (state->getStateId() != gameStates.back()->getStateId()))
	{
		gameStates.back()->onExit();
		gameStates.push_back(state);
		gameStates.back()->onEnter();
	}	
}

void
GameStateMachine::popState()
{
	if(!gameStates.empty())
	{
		if(gameStates.back()->onExit())
		{
		    GameState *temp = gameStates.back();
			gameStates.pop_back();
			delete temp;
		}
	}
}

void
GameStateMachine::changeState(GameState* state)
{
	if(!gameStates.empty())
	{
		if(gameStates.back()->getStateId() == state->getStateId())
			return;

		popState();
	}

	gameStates.push_back(state);
	gameStates.back()->onEnter();
}

