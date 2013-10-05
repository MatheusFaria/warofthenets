#include "game.h"
#include "image.h"
#include "render.h"
#include "text.h"
#include "sdlsettings.h"
#include "rectangle.h"
#include "pixel.h"
#include "line.h"
#include "circle.h"

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

	rend->clear();

	Image logo;
	logo.loadImage("resources/img/logo.png", rend->getRenderer());
	rend->renderTexture(logo.getTexture(), 10, 10);

	Text * phrase = new Text("Apresenta: ", 32);
	phrase->setFont("resources/font/Army.ttf");
	SDL_Color whiteColor = {255, 255, 255, 0};
	phrase->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	rend->renderTexture(phrase->getTexture(), 100, 500);

	Rectangle * rect = new Rectangle(50, 50);
	rect->init();
	rect->setDrawColor(255,255,255,255);
	rect->draw();

	rend->renderTexture(rect->generateTexture(rend->getRenderer()), 400, 10);

	Pixel *pix = new Pixel(); 
	pix->init();
	pix->setDrawColor(255,0,0,255);
	pix->draw();

	rend->renderTexture(pix->generateTexture(rend->getRenderer()), 400, 10);
	for(int i = 0; i < 180; i+=30)
	{
		Line *line = new Line(200, i);
		line->init();
		line->setDrawColor(150, 90 + i, 150, 255);
		line->draw();	
		rend->renderTexture(line->generateTexture(rend->getRenderer()), 450, 200);
		delete line;
	}
	
	Circle * circ = new Circle(50);
	circ->init();
	circ->setDrawColor(150, 0, 255, 255);
	circ->draw();
	rend->renderTexture(circ->generateTexture(rend->getRenderer()), 450, 200);

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
