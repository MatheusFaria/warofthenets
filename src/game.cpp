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
#include <ctime>

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
	this->window = new Window(1280, 700, 0, 0, title);
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
	
	gameStateMachine->update();
    render();
	
	while(!quit)
	{
	    
        while(SDL_PollEvent(&event))
        {
            //cout << "Event: " << event.type << endl;
            //1027
            
	        if(event.type == SDL_QUIT)
		        quit = true;
		    else
		        inputHandler->sendSdlEvent(event);
	        
	        
        }
		
		
	    gameStateMachine->update();
	    render();
	    
	    SDL_Delay(36);
	}
		
	gameStateMachine->popState();
}

void
Game::presentation()
{
    //cout << "\n\nPRESENTATION\n" << endl;
    
    
    
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
	SDL_Delay(2000);
    
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
