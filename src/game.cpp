#include "game.h"
#include "image.h"
#include "render.h"
#include "text.h"
#include "sdlsettings.h"
#include "rectangle.h"
#include "pixel.h"
#include "line.h"
#include "circle.h"
#include "hexagon.h"
#include <cmath>

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

	if(SDLSettings::setUpEnviroment())
		cout << "Enviroment Set" << endl;
	else
		cout << "Could not Set Enviroment" << endl;

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
	Render * rend = this->window->getRender();
	
	SDL_Color whiteColor = {255, 255, 255, 255};
	rend->clear();

	Image background;
	background.loadImage("resources/img/armybackground.png", rend->getRenderer());
	rend->renderTexture(background.getTexture(), 0, 0);


	Image ageClass;
	ageClass.loadImage("resources/img/ageclassification.png", rend->getRenderer());
	rend->renderTexture(ageClass.getTexture(), 600, 450);

	Image logo;
	logo.loadImage("resources/img/logomini.png", rend->getRenderer());
	rend->renderTexture(logo.getTexture(), 350, 400);

	Image mitLicense;
	mitLicense.loadImage("resources/img/mitlicense.png", rend->getRenderer());
	rend->renderTexture(mitLicense.getTexture(), 10, 400);
	
	Text * gameName = new Text("WAR OF THE NETS", 80);
	gameName->setFont("resources/font/Army.ttf");
	gameName->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int gameNameX = (this->window->getWidth() / 2) - (gameName->getWidth() / 2);
	int gameNameY = (this->window->getHeight() / 2) - (gameName->getHeight() / 2);
	rend->renderTexture(gameName->getTexture(), gameNameX, gameNameY);
	
	rend->present();
	SDL_Delay(5000);
	
	
	SDL_SetRenderDrawColor(rend->getRenderer(), 255, 255, 255, 255);
	rend->clear();

	Hexagon * hex = new Hexagon(50);
	hex->init();
	hex->setDrawColor(0, 0, 0, 255);
	hex->draw();

	for(int i = 0, j = 0, ind = 0; i < this->window->getWidth(); i+= hex->getWidth() - hex->getWidth()/4 - 2, ind++)
	{
		if(ind % 2)
			j = hex->getHeight()/2;
		else
			j = 0;
		for(; j < this->window->getHeight(); j+= hex->getHeight() -1)
		{
			rend->renderTexture(hex->generateTexture(rend->getRenderer()), i, j);
		}
	}

	rend->present();
	
	
	cout << "Renderer" << endl;
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
