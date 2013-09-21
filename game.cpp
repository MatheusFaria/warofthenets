#include "game.h"

#include <iostream>
using namespace std;

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
}

void Game::init()
{
	cout << "Intialize" << endl;

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	if(SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_VIDEO)
		cout << "Video Initialized" << endl;
	else
		cout << "ERROR in Video Initialization: [" << SDL_GetError() << "]" << endl;

	this->window = SDL_CreateWindow("War of the Nets", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									800, 600, SDL_WINDOW_SHOWN);//SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	if(!(this->window))
		cout << "The Window Could Not Be Created: [" << SDL_GetError() << "]" << endl;

}

void Game::run()
{
	cout << "Run" << endl;
	SDL_Delay(3000);
}

Game::~Game()
{
	cout << "Finishing War of the Nets" << endl;
	SDL_DestroyWindow(this->window);
}

