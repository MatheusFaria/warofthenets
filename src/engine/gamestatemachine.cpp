#include "gamestatemachine.h"

GameStateMachine::GameStateMachine()
{

}

GameStateMachine::~GameStateMachine()
{

}

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
GameStateMachine::pushState(GameState* state)
{
	if(state != NULL)
	{
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
			gameStates.pop_back();
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

