#include "game.h"
#include "render.h"
#include "text.h"
#include "sdlsettings.h"
#include "rectangle.h"
#include "pixel.h"
#include "line.h"
#include "circle.h"
#include "hexagon.h"
#include "image.h"
#include <cmath>
#include "texturemanager.h"
#include "menustate.h"
#include "inputhandler.h"
#include "soundmanager.h"

#include <iostream>
using namespace std;

#define PLAY_GAME 1
#define WIDTH 1280
#define HEIGHT 700

const int FPS = 30;
const int DELAY = 1000.0f / FPS;

Game* Game::instance = NULL;

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
}

Game* 
Game::Instance()
{
	if(Game::instance == NULL)
	{
		instance = new Game();
		return instance;
	}
		
	return instance;
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

	SoundManager::Instance()->loadSound("resources/audio/Black_Vortex.ogg", "theme", MUSIC);
	SoundManager::Instance()->playMusic("theme", 1);
}

GameStateMachine*
Game::getStateMachine()
{
	return gameStateMachine;
}

Window*
Game::getWindow()
{
	return this->window;
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

	Uint32 frameStart, frameTime;

	SDL_Event event;	
	while(!quit)
	{

		frameStart = SDL_GetTicks();

	    while(SDL_PollEvent(&event))
	    {

	        InputHandler::Instance()->update(event);
		    gameStateMachine->update();
		    render();	

		    if(event.type == SDL_QUIT)
		        quit = true;
		    
	    }

	    frameTime = SDL_GetTicks() - frameStart;

	    if(frameTime < DELAY)
        {
               SDL_Delay((int)(DELAY - frameTime));
        }
	}
}


void
Game::presentation()
{
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
	phrase->setPosition(phraseX, phraseY);
	rend->present();
	
	SDL_Delay(5000);
	
	
	rend->clear();
	
	Text * gameName = new Text("WAR OF THE NETS", 64);
	gameName->setFont("resources/font/Army.ttf");
	gameName->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int gameNameX = (this->window->getWidth() / 2) - (gameName->getWidth() / 2);
	int gameNameY = (this->window->getHeight() / 2) - (gameName->getHeight() / 2);
	gameName->setPosition(gameNameX, gameNameY);
	rend->renderTexture(gameName->getTexture(), gameNameX, gameNameY);
	
	rend->present();
	
}

void 
Game::clean()
{
    cout << "cleaning game"<<endl;
    
    gameStateMachine->clean();
    
    gameStateMachine = 0;
    delete gameStateMachine;
    
    TextureManager::Instance()->clearTextureMap();
    
    SDL_DestroyRenderer(Render::getInstance()->getRenderer());
    SDL_Quit();
}

void updateTime();
void getInput();	
void getNetworkMessage();
void simulateWorld();
void updateObjects();
void renderWorld();

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
