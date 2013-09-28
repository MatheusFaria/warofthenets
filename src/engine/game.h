#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "window.h"

class Game{

public:
	Game();
	~Game();

	void init();
	void run();
	void presentation();
	void mainLoop();
	void menu();

private:
	Window * window;

};

#endif
