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
	this->window = new Window(1280, 700, 0, 0, title);
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
	SDL_SetRenderDrawColor(rend->getRenderer(), 255, 255, 255, 255);
	rend->clear();
	
	int xcenter = 250, ycenter = 100;

	Image logo;
	logo.loadImage("resources/img/apresentacao.png", rend->getRenderer());
	rend->renderTexture(logo.getTexture(), xcenter, ycenter);
	
	rend->present();
	
	SDL_Delay(3000);
	
	rend->clear();

	Image tecs;
	tecs.loadImage("resources/img/tecnologias.png", rend->getRenderer());
	rend->renderTexture(tecs.getTexture(), xcenter, ycenter);
	
	rend->present();
	
	SDL_Delay(3000);
	
	rend->clear();

	Image requisitos;
	requisitos.loadImage("resources/img/requisitoslegais.png", rend->getRenderer());
	rend->renderTexture(requisitos.getTexture(), xcenter, ycenter);
	
	rend->present();
	
	SDL_Delay(3000);
	
	rend->clear();

	Image background;
	background.loadImage("resources/img/armybackground.png", rend->getRenderer());
	rend->renderTexture(background.getTexture(), 0, 0);
	
	Text * gameName = new Text("WAR OF THE NETS", 80);
	gameName->setFont("resources/font/Army.ttf");
	gameName->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int gameNameX = (this->window->getWidth() / 2) - (gameName->getWidth() / 2);
	int gameNameY = (this->window->getHeight() / 2) - (gameName->getHeight() / 2);
	rend->renderTexture(gameName->getTexture(), gameNameX, gameNameY);
	
	rend->present();
	
	SDL_Delay(5000);
	
	
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
    int eixoX, eixoY;
    
    Image torreUm;
	torreUm.loadImage("resources/img/torre01.png", rend->getRenderer());
	
	Image torreDois;
	torreDois.loadImage("resources/img/torre02.png", rend->getRenderer());
	
	Image torreTres;
	torreTres.loadImage("resources/img/torre03.png", rend->getRenderer());
	
	Image spyUnit;
	spyUnit.loadImage("resources/img/spyunit01.png", rend->getRenderer());
	
	Image base;
	base.loadImage("resources/img/base.png", rend->getRenderer());
		
	
	eixoX = 1 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = 1 * (hex->getHeight() -1);	
	rend->renderTexture(torreUm.getTexture(), eixoX, eixoY);
	
	eixoX = 3 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = 0 * (hex->getHeight() -1);	
	rend->renderTexture(torreUm.getTexture(), eixoX, eixoY);
	
	eixoX = 4 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (2 * (hex->getHeight() -1)) - (hex->getHeight()/2);	
	rend->renderTexture(torreUm.getTexture(), eixoX, eixoY);
	
	eixoX = 5 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = 0 * (hex->getHeight() -1);	
	rend->renderTexture(torreDois.getTexture(), eixoX, eixoY);
	
	eixoX = 1 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (3 * (hex->getHeight() -1));
	rend->renderTexture(torreDois.getTexture(), eixoX, eixoY);
	
	eixoX = 6 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (2 * (hex->getHeight() -1)) - (hex->getHeight()/2);	
	rend->renderTexture(torreDois.getTexture(), eixoX, eixoY);
	
	eixoX = 3 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (3 * (hex->getHeight() -1));
	rend->renderTexture(torreTres.getTexture(), eixoX, eixoY);
    
    eixoX = 2 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (2 * (hex->getHeight() -1)) - (hex->getHeight()/2);
	rend->renderTexture(torreTres.getTexture(), eixoX, eixoY);
	
	eixoX = 0 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (1 * (hex->getHeight() -1)) - (hex->getHeight()/2);
	rend->renderTexture(torreTres.getTexture(), eixoX, eixoY);
	
	eixoX = 4 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = (4 * (hex->getHeight() -1));
	rend->renderTexture(spyUnit.getTexture(), eixoX, eixoY);
	
	eixoX = 7 * (hex->getWidth() - (hex->getWidth()/4) - 2);
	eixoY = 0 * (hex->getHeight() -1) + (hex->getHeight()/2);	
	rend->renderTexture(spyUnit.getTexture(), eixoX, eixoY);
	
	eixoX = 0 * (hex->getWidth() - (hex->getWidth()/4) - 2) + (hex->getWidth()/4);
	eixoY = (4 * (hex->getHeight() -1)) + (hex->getHeight()/4) + (hex->getHeight()/2);
	rend->renderTexture(base.getTexture(), eixoX, eixoY);
	
    
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
