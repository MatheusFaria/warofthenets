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

#include "testLevelState.h"
#include "input_handler.h"

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
	
	this->gameStateMachine = new GameStateMachine();
	
	//cout << "\ngameStateMachine: " << gameStateMachine << endl;
	
	
	
	this->gameStateMachine->changeState(new TestLevelState(this->window->getWidth()
	                                                , this->window->getHeight()
	                                                , this->window->getRender()));
    
    
}

void
Game::render()
{
    Render * rend = this->window->getRender();
    
	rend->clear();
	gameStateMachine->render();
	rend->present();
}

void
Game::run()
{
	cout << "Run" << endl;

	bool quit = false;
	InputHandler *inputHandler = InputHandler::getInstance();
	
	presentation();
	
	SDL_Event event;	
	while(!quit)
	{
        SDL_PollEvent(&event);
        
	    if(event.type == SDL_QUIT)
		    quit = true;
		else
		    inputHandler->sendSdlEvent(event);
        
		
		
	    gameStateMachine->update();
	    render();
	}
}

void
Game::presentation()
{
    //cout << "\n\nPRESENTATION\n" << endl;
    /*
    this->gameStateMachine->update();
    this->gameStateMachine->render();
    */
    
    /*
	Render * rend = this->window->getRender();

	rend->clear();

	Image logo;
	
	logo.loadImage("resources/img/logo.png", rend->getRenderer());
	int logoX = (this->window->getWidth() / 2) - (logo.getWidth() / 2);
	int logoY = (this->window->getHeight() / 2) - (logo.getHeight() / 2);
	rend->renderTexture(logo.getTexture(), logoX, logoY);
	

	Text * phrase = new Text("Apresenta: ", 32);
	phrase->setFont("resources/font/Army.ttf");
	SDL_Color whiteColor = {255, 255, 255, 0};
	phrase->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int phraseX = logoX + (phrase->getWidth() / 2);
	int phraseY = (logoY + logo.getHeight() + 15);
	rend->renderTexture(phrase->getTexture(), phraseX, phraseY);
    
	rend->present();
	
	SDL_Delay(5000);
	
	
	rend->clear();
	
	Text * gameName = new Text("WAR OF THE NETS", 64);
	gameName->setFont("resources/font/Army.ttf");
	gameName->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int gameNameX = (this->window->getWidth() / 2) - (gameName->getWidth() / 2);
	int gameNameY = (this->window->getHeight() / 2) - (gameName->getHeight() / 2);
	rend->renderTexture(gameName->getTexture(), gameNameX, gameNameY);
	
	rend->present();
	
	
	SDL_Delay(5000);
	
	rend->clear();
	
	
	Hexagon * hex = new Hexagon(140);
	hex->init();
	hex->setDrawColor(150, 255, 255, 255);
	hex->draw();
	rend->renderTexture(hex->generateTexture(rend->getRenderer()), 0, 0);
	
	Image torre;
	torre.loadImage("resources/img/torre.png", rend->getRenderer());
	int torreX = 0 + (hex->getWidth() / 2) - (torre.getWidth() / 2);
	int torreY = 0 + (hex->getHeight() / 2) - (torre.getHeight() / 2);
	rend->renderTexture(torre.getTexture(), torreX, torreY);
	
	Hexagon * hex2 = new Hexagon(140);
	hex2->init();
	hex2->setDrawColor(150, 255, 255, 255);
	hex2->draw();
	rend->renderTexture(hex2->generateTexture(rend->getRenderer()), hex->getWidth(), 0);
	
	Image base;
	base.loadImage("resources/img/base.png", rend->getRenderer());
	int baseX = hex->getWidth() + (hex2->getWidth() / 2) - (base.getWidth() / 2);
	int baseY = 0 + (hex2->getHeight() / 2) - (base.getHeight() / 2);
	rend->renderTexture(base.getTexture(), baseX, baseY);
	
	Hexagon * hex3 = new Hexagon(140);
	hex2->init();
	hex2->setDrawColor(150, 255, 255, 255);
	hex2->draw();
	int h = ((hex->getHeight() / (sqrt(3)*2))/2) - 2;
	rend->renderTexture(hex2->generateTexture(rend->getRenderer()), hex->getWidth(), hex->getHeight() - h);
	
	torreX = hex->getWidth() + (hex3->getWidth() / 2) - (torre.getWidth() / 2);
	torreY = (hex->getHeight() - h) + (hex3->getHeight() / 2) - (torre.getHeight() / 2);
	rend->renderTexture(torre.getTexture(), torreX, torreY);
	
	rend->present();
	
	cout << "Renderer" << endl;
	*/
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
