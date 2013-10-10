#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "gameestate.h"
#include <vector>

class GameStateMachine{

public:

	GameStateMachine(){};

	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();

	void update();
	void render();

private:

	std::vector<GameState*> gameStates;

};

#endif