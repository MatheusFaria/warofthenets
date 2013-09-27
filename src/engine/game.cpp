#include "game.h"
#include "gametime.h"
#include "image.h"
#include "render.h"

#include <iostream>
using namespace std;

#define PLAY_GAME 1

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

	const char * title = "War of The Nets";
	this->window = new Window(800, 600, 0, 0, title);
	(this->window)->createWindow();
}

Game::~Game()
{
	cout << "Finishing War of the Nets" << endl;
	delete window;
}

void updateTime();
void getInput();	
void getNetworkMessage();
void simulateWorld();
void updateObjects();
void renderWorld();

void Game::run()
{
	cout << "Run" << endl;

	bool quit = false;
	
	presentation();
	
	SDL_Event event;	
	while(!quit)
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			quit = true;//menu();
	}
}

void
Game::presentation()
{
	Image logo;
	Render rend = this->window->getRender();
	logo.loadImage("resources/img/logo.bmp", rend.getRenderer());
	rend.clear();
	rend.renderImage(logo, 10, 10);
	rend.present();
}

void
Game::mainLoop()
{
	isFinished = false;

	while(!isFinished)
	{
		updateTime();
		getInput();	
		getNetworkMessage();
		simulateWorld();
		updateObjects();
		renderWorld();
		isFinished = true;
	}
}

void
Game::menu()
{
	int choice = 0;
	
	if(choice == PLAY_GAME)
		mainLoop();
}

void updateTime()
{
	GameTime* time = new GameTime();

	if(time != NULL)
		cout<<"Update time"<<endl;
}

void getInput()
{
	cout<<"Inputs received"<<endl;
}

void getNetworkMessage()
{
	cout<<"Getting Network Message"<<endl;
}

void simulateWorld()
{
	cout<<"Simulating world units"<<endl;
}

void updateObjects()
{
	cout<<"Onjects atualized"<<endl;
}

void renderWorld()
{
	cout<<"World Screen Atualized"<<endl;
}
