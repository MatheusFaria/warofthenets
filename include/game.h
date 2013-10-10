#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "window.h"
#include "gamestatemachine.h"

class Game{

public:
	Game();
	~Game();

	void init();
	void run();
	void render();
	void presentation();
	void mainLoop();
	void menu();

private:
	Window * window;
	GameStateMachine* gameStateMachine;

};

#endif
