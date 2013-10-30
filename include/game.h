#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "window.h"
#include "gamestatemachine.h"

class Game{

public:

	Game();
	~Game();
	static Game* Instance();

	void init();
	void run();
	void render();
	void presentation();
	void mainLoop();
	void menu();
	void clean();
	
	bool isFinish();
	void finishGame();

	GameStateMachine* getStateMachine();
	Window* getWindow();

private:

	static Game* instance;
	Window * window;
	GameStateMachine* gameStateMachine;
	
	bool finish;

};

#endif
