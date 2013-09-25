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

private:
	Window * window;
	bool isFinished;

};

#endif
