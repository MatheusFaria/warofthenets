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

int getRectX(int posX, Hexagon *hex, Rectangle *rect)
{
    int x = (posX * hex->getWidth()) - (posX + ((posX-1) - ((posX-1)/4))) - ((posX * hex->getWidth()) / 4) + (hex->getWidth() / 2) - (rect->getWidth() / 2);
    return x;
}

int getRectY(int posX, int posY, Hexagon *hex, Rectangle *rect)
{
    int y = (posY * hex->getHeight()) + (hex->getHeight() / 2) - (rect->getHeight() / 2);
    
    if(posX % 2 != 0)
        y += hex->getHeight() / 2;
    
    return y;
}

void
Game::presentation()
{
	Render * rend = this->window->getRender();

	rend->clear();

	Image logo;
	
	SDL_Color whiteColor = {255, 255, 255, 255};
		
	Hexagon * hex = new Hexagon(50);
	hex->init();
	hex->setDrawColor(150, 255, 255, 255);
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
	
	Rectangle * rect = new Rectangle(50, 70);
	rect->init();
	rect->setDrawColor(0, 0, 255, 255);
	rect->draw();

	    
    int x = getRectX(3, hex, rect);
    int y = getRectY(3, 4, hex, rect);
	rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
	
	x = getRectX(0, hex, rect);
    y = getRectY(0, 4, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
    
    x = getRectX(1, hex, rect);
    y = getRectY(1, 2, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
    
    x = getRectX(4, hex, rect);
    y = getRectY(4, 2, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);

    
    rect->setDrawColor(255, 0, 0, 255);
	rect->draw();
	
	
	x = getRectX(5, hex, rect);
    y = getRectY(5, 2, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
    
	x = getRectX(9, hex, rect);
    y = getRectY(9, 0, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
    
	x = getRectX(8, hex, rect);
    y = getRectY(8, 2, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
    
	x = getRectX(7, hex, rect);
    y = getRectY(7, 3, hex, rect);
    rend->renderTexture(rect->generateTexture(rend->getRenderer()), x , y);
    
    
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
