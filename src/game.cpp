#include "game.h"
#include "render.h"
#include "text.h"
#include "sdlsettings.h"
#include "texturemanager.h"
#include "menustate.h"
#include "inputhandler.h"

#include <iostream>
using namespace std;

#define PLAY_GAME 1
#define WIDTH 1280
#define HEIGHT 700

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

	if(SDLSettings::setUpEnviroment())
		cout << "Enviroment Set" << endl;
	else
		cout << "Could not Set Enviroment" << endl;

	const char * title = "War of The Nets";
	this->window = new Window(WIDTH, HEIGHT, 0, 0, title);
	(this->window)->createWindow();

	this->gameStateMachine = new GameStateMachine();
	this->gameStateMachine->changeState(new MenuState());
}

void
Game::render()
{
	Render::getInstance()->clear();
	gameStateMachine->render();
	Render::getInstance()->present();
}

void
Game::run()
{
	cout << "Run" << endl;

	bool quit = false;
	
	presentation();
	SDL_Delay(2000);

	
	
	SDL_Event event;	
	while(!quit)
	{
	    while(SDL_PollEvent(&event))
	    {
	        InputHandler::Instance()->update(event);
		    gameStateMachine->update();
		    render();
		    
		    //cout << "Renderizado" << endl;
		    
		    if(event.type == SDL_QUIT)
		        quit = true;
	    }
	}
}

void
Game::presentation()
{
	Render * rend = this->window->getRender();
    TextureManager::Instance()->loadImage("resources/img/logo.bmp", "logo", rend->getRenderer());
    rend->clear();
    TextureManager::Instance()->draw("logo", 0,0, rend->getRenderer());
    rend->present();


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
