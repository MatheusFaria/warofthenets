#include "game.h"
#include "image.h"
#include "render.h"
#include "text.h"

#include <iostream>
using namespace std;

#define PLAY_GAME 1

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
}

Game::~Game()
{
	cout << "Finishing War of the Nets" << endl;
	if(window != NULL)
		delete window;
}

void
Game::init()
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


void
Game::run()
{
	cout << "Run" << endl;

	bool quit = false;
	
	presentation();
	
	SDL_Event event;	
	while(!quit)
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			quit = true;
	}
}

void
Game::presentation()
{
	Image logo;
	Render * rend = this->window->getRender();
	logo.loadImage("resources/img/logo.bmp", rend->getRenderer());
	rend->clear();
	rend->renderTexture(logo.getTexture(), 10, 10);

	Text * phrase = new Text("Apresenta: ", 32);
	phrase->setFont("resources/fonts/Army.ttf");
	SDL_Color whiteColor = {255, 255, 255, 0};
	phrase->generateTexture(rend->getRenderer(), whiteColor, whiteColor);

	rend->renderTexture(phrase->getTexture(), 100, 500);
	rend->present();
}

void
Game::menu()
{
	int choice = 0;
	
	if(choice == PLAY_GAME)
		mainLoop();
}

void updateTime();
void getInput();	
void getNetworkMessage();
void simulateWorld();
void updateObjects();
void renderWorld();

void
Game::mainLoop()
{
	bool levelComplete = false;

	while(!levelComplete)
	{
		updateTime();
		getInput();	
		getNetworkMessage();
		simulateWorld();
		updateObjects();
		renderWorld();
		levelComplete = true;
	}
}

void updateTime()
{
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
