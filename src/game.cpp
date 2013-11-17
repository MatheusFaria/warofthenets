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

#include "networkstate.h"

#include <iostream>
using namespace std;

#define PLAY_GAME 1
#define WIDTH 1280
#define HEIGHT 700

const int FPS = 60;
const int DELAY = 1000.0f / FPS;

Game* Game::instance = NULL;

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
	finish = false;
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
	
	SDL_SetRenderDrawBlendMode(this->window->getRender()->getRenderer(), SDL_BLENDMODE_BLEND);

	this->gameStateMachine = new GameStateMachine();
	//this->gameStateMachine->changeState(new MenuState());
	this->gameStateMachine->changeState(new NetworkState());
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

//	presentation();
	//SDL_Delay(2000);
	
	Uint32 frameStart, frameTime;
	
	SDL_Event event;	
	while(!isFinish())
	{
	    frameStart = SDL_GetTicks();
	    
	    while(SDL_PollEvent(&event))
	    {
	        InputHandler::getInstance()->sendSdlEvent(event);
		    
		    if(event.type == SDL_QUIT)
		        finishGame();
	    }
	    
	    gameStateMachine->update();
	    
	    frameTime = SDL_GetTicks() - frameStart;
	    
	    if(frameTime < (Uint32) DELAY)
	    {
	        render();
	        
	        frameTime = SDL_GetTicks() - frameStart;
	        
	        if(frameTime < (Uint32) DELAY)
            {
                SDL_Delay((int)(DELAY - frameTime - 1));
            }
	    }/*else{
	        cout << "PULOU!" << endl;
	    }*/
	    
	    frameTime = SDL_GetTicks() - frameStart;
	    
	    //cout << "frameTime: " << frameTime << endl;
	    //cout << "DELAY: " << DELAY << endl;
	    
	    SDL_Delay(1);
	}
}


void
Game::presentation()
{
    Image logo("resources/img/logo.png");
    int logoX = (this->window->getWidth() / 2) - (logo.getWidth() / 2);
	int logoY = (this->window->getHeight() / 2) - (logo.getHeight() / 2);
    logo.setPosition(logoX, logoY);
    
    SDL_Color blackColor = {0, 0, 0, 0};
    
    Text phrase("Apresenta: ", 32);
    phrase.setFont("resources/font/Army.ttf");
    phrase.setColor(blackColor);
    int phraseX = logoX + (phrase.getWidth() / 2);
	int phraseY = (logoY + logo.getHeight() + 15);
	phrase.setPosition(phraseX, phraseY);
    
    SDL_Renderer *rend = this->window->getRender()->getRenderer();
    SDL_Rect rectBackground = {0, 0, WIDTH, HEIGHT};
    
    Image sdl("resources/img/sdl.png");
    int sdlX = (this->window->getWidth() / 2) - (sdl.getWidth() / 2);
	int sdlY = (this->window->getHeight() / 2) - (sdl.getHeight() / 2);
    sdl.setPosition(sdlX, sdlY);
    
    Image mit("resources/img/mit.png");
    int mitX = (this->window->getWidth() / 2) - (mit.getWidth() / 2);
	int mitY = (this->window->getHeight() / 2) - (mit.getHeight() / 2);
    mit.setPosition(mitX, mitY);
    
    Image gameName("resources/img/gamename.png");
        
    for(int i = 255; i >= 0; i -= 3)
    {
        Render::getInstance()->clear();
        
        logo.draw();
        phrase.draw();
        
        SDL_SetRenderDrawColor(rend, 255, 255, 255, i);
        SDL_RenderFillRect(rend, &rectBackground);
        
        Render::getInstance()->present();
    }
        
    for(int i = 255; i >= 0; i -= 4)
    {
        Render::getInstance()->clear();
        
        sdl.draw();
        
        SDL_SetRenderDrawColor(rend, 255, 255, 255, i);
        SDL_RenderFillRect(rend, &rectBackground);
        
        Render::getInstance()->present();
    }
    
    for(int i = 255; i >= 0; i -= 4)
    {
        Render::getInstance()->clear();
        
        mit.draw();
        
        SDL_SetRenderDrawColor(rend, 255, 255, 255, i);
        SDL_RenderFillRect(rend, &rectBackground);
        
        Render::getInstance()->present();
    }
    
    for(int i = 255; i >= 0; i -= 4)
    {
        Render::getInstance()->clear();
        
        gameName.draw();
        
        SDL_SetRenderDrawColor(rend, 255, 255, 255, i);
        SDL_RenderFillRect(rend, &rectBackground);
        
        Render::getInstance()->present();
    }
    
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

bool
Game::isFinish()
{
    return finish;
}

void
Game::finishGame()
{
    finish = true;
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
