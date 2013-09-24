#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

class Game{

public:
	Game();
	~Game();

	void init();
	void run();

private:
	SDL_Window * window;
	bool isFinished;

};

#endif
