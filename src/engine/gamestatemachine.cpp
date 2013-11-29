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
	    if(gameStates.size() > 0)
		    gameStates.back()->disable();
	    
		gameStates.push_back(state);
		gameStates.back()->onEnter();
		gameStates.back()->enable();		
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
			
			if(gameStates.size() > 0)
			    gameStates.back()->enable();
			    
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
	//gameStates.back()->enable();
}

