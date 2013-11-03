#include "playstate.h"
#include "gameoverstate.h"
#include "render.h"
#include "game.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"
#include "torre.h"
#include <algorithm>
#include <iostream>


const std::string PlayState::playId = "PLAY";

void
PlayState::update()
{
	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->update();

	for(int i =0; i<(int)vectorHexagon.size(); i++)
		vectorHexagon[i]->update();
	
	
	txtNumTower->setText(std::to_string(numTower));
	txtNumBomb->setText(std::to_string(numBomb));
	txtNumSpy->setText(std::to_string(numSpy));
}

void
PlayState::render()
{
	//createMap();
	
	for(int i =0; i<(int)vectorHexagon.size(); i++)
		vectorHexagon[i]->draw();

	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->draw();

	
	txtNumTower->draw();
	txtNumBomb->draw();
	txtNumSpy->draw();
}

bool
PlayState::onEnter()
{
	windowWidth = Game::Instance()->getWindow()->getWidth();
	windowHeight =
	Game::Instance()->getWindow()->getHeight();

	

	Render::getInstance()->setColor(255, 255, 255 , 255);
	

	idSelected = "";

	//InputHandler::getInstance()->addMouseClick(this);

	createMap();
	createHUD();
	
	numTower = 0;
	numBomb = 0;
	numSpy = 0;
	
	

	std::cout<<"Play State"<<std::endl;
	return true;
}

void
PlayState::createMap()
{

	const float yOff = 0.87*50;
	const float xOff =0.5*50;

	unsigned int numColumns = windowWidth/75;
	unsigned int numRows = windowHeight/87;

	std::cout<<numColumns<<" "<<numRows<<std::endl;

	for(unsigned int i =0; i<numRows; i++)
	{	
		for(unsigned int j = 0; j<numColumns; j++)
		{
			float yPos = i*yOff*2;

			if(j%2 != 0)
				yPos += yOff;

			const float xPos = j*xOff*3;

			Hexagon *hex = new Hexagon(50, Render::getInstance());
			hex->setDrawColor(0, 0, 0 , 255);
			hex->setPosition(xPos, yPos);
			vectorHexagon.push_back(hex);
			hex->setEventListener(this);
			InputHandler::getInstance()->addMouseClick(hex);
		}
	}	
}

bool 
PlayState::onExit()
{
    InputHandler::getInstance()->removeMouseClick(quit);
    InputHandler::getInstance()->removeMouseClick(recursoSpy);
    InputHandler::getInstance()->removeMouseClick(recursoBomb);
    InputHandler::getInstance()->removeMouseClick(recursoTower);
    InputHandler::getInstance()->removeMouseClick(painelRecurso);

    for(int i =0; i<(int)playObjects.size(); i++)
	{
		playObjects[i]->clean();
		delete playObjects[i];
    }
    

    for(int i =0; i<(int)vectorHexagon.size(); i++)
		delete vectorHexagon[i];

    delete txtNumTower;
	delete txtNumBomb;
	delete txtNumSpy;
    
	return true;
}

std::string 
PlayState::getStateId() const
{
	return playId;
}

void 
PlayState::createHUD()
{
	painelRecurso = new MenuButton(0, 0, "resources/img/painelrecurso.png", "painelrecurso");
	painelRecurso->setPosition(0, windowHeight - painelRecurso->getHeight());
	painelRecurso->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(painelRecurso);

	recursoTower = new MenuButton(0, 0, "resources/img/botaorecursotorre.png", "botaorecursotorre");
	int recursoTowerX = (painelRecurso->getWidth() / 2) - (recursoTower->getWidth() / 2);
	int recursoTowerY = painelRecurso->getY() + 26;
	recursoTower->setPosition(recursoTowerX, recursoTowerY);
	recursoTower->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoTower);

	recursoBomb = new MenuButton(0, 0, "resources/img/botaorecursobomba.png", "botaorecursobomba");
	int recursoBombX = recursoTowerX;
	int recursoBombY = recursoTowerY + recursoTower->getHeight() + 7;
	recursoBomb->setPosition(recursoBombX, recursoBombY);
	recursoBomb->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoBomb);

	recursoSpy = new MenuButton(0, 0, "resources/img/botaorecursoespiao.png", "botaorecursoespiao");
	int recursoSpyX = recursoTowerX;
	int recursoSpyY = recursoBombY + recursoBomb->getHeight() + 7;
	recursoSpy->setPosition(recursoSpyX, recursoSpyY);
	recursoSpy->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoSpy);
	
	quit = new MenuButton(0, 0, "resources/img/botaosair.png", "botaosair");
	int quitX = windowWidth - quit->getWidth();
	int quitY = 0;
	quit->setPosition(quitX, quitY);
	quit->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(quit);
	
	SDL_Color blackColor = {0, 0, 0, 0};
	
	txtNumTower = new Text("0", 16);
	txtNumTower->setFont("resources/font/Army.ttf");
    txtNumTower->setColor(blackColor);
    int x = recursoTowerX + recursoTower->getWidth() - txtNumTower->getWidth() - 18;
    int y = recursoTowerY + recursoTower->getHeight() - txtNumTower->getHeight() - 9;
    txtNumTower->setPosition(x, y);
    
    txtNumBomb = new Text("0", 16);
	txtNumBomb->setFont("resources/font/Army.ttf");
    txtNumBomb->setColor(blackColor);
    x = recursoTowerX + recursoTower->getWidth() - txtNumBomb->getWidth() - 18;
    y = recursoBombY + recursoBomb->getHeight() - txtNumBomb->getHeight() - 9;
    txtNumBomb->setPosition(x, y);
    
    txtNumSpy = new Text("0", 16); 
	txtNumSpy->setFont("resources/font/Army.ttf");
    txtNumSpy->setColor(blackColor);
    x = recursoTowerX + recursoTower->getWidth() - txtNumSpy->getWidth() - 18;
    y = recursoSpyY + recursoSpy->getHeight() - txtNumSpy->getHeight() - 9;
    txtNumSpy->setPosition(x, y);


	playObjects.push_back(painelRecurso);
	playObjects.push_back(recursoTower);
	playObjects.push_back(recursoBomb);
	playObjects.push_back(recursoSpy);
	playObjects.push_back(quit);



}

void 
PlayState::onMouseClick(MouseClick *mouseClick)
{
	if(mouseClick == recursoTower)
	{
		idSelected = "resources/img/tower.png";

		std::cout << "Selecionou: TORRE" << std::endl;
	}

	if(mouseClick == recursoBomb)
	{
		idSelected = "resources/img/bomb.png";

		std::cout << "Selecionou: BOMBA" << std::endl;
	}

	if(mouseClick == recursoSpy)
	{
		idSelected = "resources/img/spy.png";

		std::cout << "Selecionou: ESPIAO" << std::endl;
	}
	
	if(mouseClick == quit)
	{
	    Game::Instance()->getStateMachine()->changeState(new GameOverState());
    }

    if(dynamic_cast<Hexagon*>(mouseClick))
    {

    	std::cout<<"Clicou no Hexagon"<<std::endl;
    	Hexagon *temp = (Hexagon *) mouseClick;

    	if(temp->isMouseLeft())
    		showObject(temp);
    	else if(temp->isMouseRight())
    	{
    		std::cout<<"Clicou no direito"<<std::endl;
    		deleteObject(temp);	
    	}	

    }
}

GameObject*
PlayState::createObject()
{
	Image* recurso = NULL;

	if(idSelected =="")
		return NULL;
	if(idSelected == "resources/img/tower.png")
    	recurso = new Torre();
	    
	else
        recurso = new Image(idSelected);
	

	return recurso;
}

void
PlayState::incObject()
{
	if(idSelected == "resources/img/tower.png")
		numTower++;
	else if(idSelected == "resources/img/bomb.png")
		numBomb++;
	else if(idSelected == "resources/img/spy.png")	
		numSpy++;
}

void
PlayState::decObject(GameObject* object)
{
	if(dynamic_cast<Torre*>(object))
		numTower--;
}

void 
PlayState::showObject(Hexagon* hex)
{
	GameObject* object = createObject();

	if(!object)
		return;
	else
	{
		if(hex->setObject(object))
		{
			incObject();
			playObjects.push_back(object);
		}	
	}
}

void
PlayState::deleteObject(Hexagon *hex)
{

	GameObject* object = hex->getObject();

	if(!object)
		return;

	vector<GameObject*>::iterator it;

	it = find(playObjects.begin(), playObjects.end(), object);
	playObjects.erase(it);

	hex->destroyGameObject();
	decObject(object);
	delete object;
}