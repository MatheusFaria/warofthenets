#include "game.h"
#include "gametime.h"

#include <iostream>
using namespace std;

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
}

void Game::init()
{
	cout << "Intialize" << endl;
}

Game::~Game()
{
	cout << "Finishing War of the Nets" << endl;
}

void updateTime();
void getInput();	
void getNetworkMessage();
void simulateWorld();
void updateObjects();
void renderWorld();

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
