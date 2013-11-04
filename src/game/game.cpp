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
#include "texture.h"
#include "imagemanager.h"
#include "networkmanager.h"

#include <iostream>
using namespace std;

#define PLAY_GAME 1
#define WIDTH 1280
#define HEIGHT 700

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
Game::init(int qtd, char * dataServer)
{
	cout << "Intialize" << endl;

	Networkmanager * network;

	if(qtd == 1)
	{
		this->server = new Server("10.1.1.1", "9000");
		this->client = NULL;
		cout << "This is a server" << endl;
	}
	else
	{
		cout << "This is a Client\nIP Server: " << dataServer[1] << "\nPort Server: " << dataServer[2] << endl;
		this->server = new Server(dataServer[1], dataServer[2]);
		this->client = new Client("10.1.1.2", "9000", server);
	}

	network = new Networkmanager(server, client);

	if(SDLSettings::setUpEnviroment())
		cout << "Enviroment Set" << endl;
	else
		cout << "Could not Set Enviroment" << endl;

	const char * title = "War of The Nets";
	this->window = new Window(WIDTH, HEIGHT, 0, 0, title);
	(this->window)->createWindow();

/*	this->gameStateMachine = new GameStateMachine();
	this->gameStateMachine->changeState(new MenuState());

	SoundManager::Instance()->loadSound("resources/audio/Black_Vortex.ogg", "theme", MUSIC);
	SoundManager::Instance()->playMusic("theme", 1);*/
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

	Render * rend = this->window->getRender();
	
	TextureManager * manager = new TextureManager();
	ImageManager * imanager = new ImageManager();

	Image * logo;
	imanager->addImage("resources/img/spritedimg2.png", rend, 4, 1, 4);
	logo = imanager->getImage("resources/img/spritedimg2.png");

	Texture * logoTex = new Texture(logo, 10, 10, true);
	Texture * logoTex2 = new Texture(logo, 100, 100);
	
	SDL_Color white = {255, 255, 255, 255};

	Text * texto = new Text("WAR OF THE NETS", 30, "resources/font/Army.ttf", white, rend);
	Texture * textoTex = new Texture(texto, 300, 10);

	Hexagon * hex = new Hexagon(50, rend);
	hex->setDrawColor(255,255,255,255);
	Texture * hexTex = new Texture(hex, 300, 300);

	Circle * rect = new Circle(30, rend);
	rect->setDrawColor(255,255,255,255);
	Texture * rectTex = new Texture(rect, 300, 400);

	manager->addTexture("rect", rectTex);
	manager->addTexture("hex", hexTex);
	manager->addTexture("texto", textoTex);
	manager->addTexture("logo1", logoTex);
	manager->addTexture("logo2", logoTex2);

	SDL_Event event;	
	while(!quit)
	{
	rend->clear();
	    while(SDL_PollEvent(&event))
	    {
	        //InputHandler::Instance()->update(event);
		    //gameStateMachine->update();
		    //render();
		    
		    if(event.type == SDL_QUIT)
		        quit = true;
			else if(event.type == SDL_KEYDOWN)
			{
				logoTex2->incSprite();
			}
	    }
	manager->renderAll();
	rend->present();
	SDL_Delay(330);
	}

	imanager->releaseImage("resources/img/spritedimg2.png");
	imanager->removeImage("resources/img/spritedimg2.png");
}


void
Game::presentation()
{

/*
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
*/
}

void 
Game::clean()
{
    cout << "cleaning game"<<endl;
    
   /* gameStateMachine->clean();
    
    gameStateMachine = 0;
    delete gameStateMachine;
    
    TextureManager::Instance()->clearTextureMap();*/
    
    SDL_DestroyRenderer(Render::getInstance()->getRenderer());
    SDL_Quit();
}
