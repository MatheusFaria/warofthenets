#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "window.h"
#include "gamestatemachine.h"
#include "client.h"
#include "server.h"

class Game{

public:

	Game();
	~Game();
	static Game* Instance();

	void init(int, char *);
	void run();
	void render();
	void presentation();
	void mainLoop();
	void menu();
	void clean();

	GameStateMachine* getStateMachine();
	Window* getWindow();

private:

	static Game* instance;
	Window * window;
	GameStateMachine* gameStateMachine;
	Client * client;
	Server * server;

};

#endif
