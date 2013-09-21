#include "game.h"
#include "game_time.h"

#include <iostream>
using namespace std;

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
}

void Game::init()
{
	cout << "Intialize" << endl;

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	if(SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_VIDEO)
		cout << "Video Initialized" << endl;
	else
		cout << "ERROR in Video Initialization: [" << SDL_GetError() << "]" << endl;

	this->window = SDL_CreateWindow("War of the Nets", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
									800, 600, SDL_WINDOW_SHOWN);//SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	if(!(this->window))
		cout << "The Window Could Not Be Created: [" << SDL_GetError() << "]" << endl;

}

//Atualizar tempo de jogo
void updateTime()
{
	GameTime* time = new GameTime();

	if(time != NULL)
		cout<<"Update time"<<endl;

}

void getInput()
{
	cout<<"Inputs received"<<endl;
}

//Funcao que ira simular o comportamento de conexao de uma rede
void getNetworkMessage()
{
	cout<<"Getting Network Message"<<endl;
}

//Atualizar os elementos lógicos contidos no jogo
void simulateWorld()
{
	cout<<"Simulating world units"<<endl;
}

//Atualizar o estado dos objetos contidos no jogo
void updateObjects()
{
	cout<<"Onjects atualized"<<endl;
}

//Atualizar as telas do jogo
void renderWorld()
{
	cout<<"World Screen Atualized"<<endl;
}



void Game::run()
{
	cout << "Run" << endl;

	isFinished = false;

	while(!isFinished)
	{
		updateTime();
		getInput();	
		getNetworkMessage();
		simulateWorld();
		updateObjects();
		renderWorld();
		isFinished = true;
	}	

	SDL_Delay(3000);
}

Game::~Game()
{
	cout << "Finishing War of the Nets" << endl;
	SDL_DestroyWindow(this->window);
}

