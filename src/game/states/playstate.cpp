#include "playstate.h"
#include "gameoverstate.h"
#include "render.h"
#include "game.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"
#include "torre.h"
#include <iostream>


const std::string PlayState::playId = "PLAY";

void
PlayState::update()
{
	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->update();
	
	
	txtNumTower->setText(std::to_string(numTower));
	txtNumBomb->setText(std::to_string(numBomb));
	txtNumSpy->setText(std::to_string(numSpy));
}

void
PlayState::render()
{
	createMap();
	

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
	windowHeight = Game::Instance()->getWindow()->getHeight();

	hex = new Hexagon(50, Render::getInstance());
	hex->setDrawColor(0, 0, 0 , 255);
	hex->setPosition(200, 200);

	Render::getInstance()->setColor(255, 255, 255 , 255);
	

	idSelected = "";

	InputHandler::getInstance()->addMouseClick(this);

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
	for(int i = 0, j = 0, ind = 0; i < windowWidth; i+= hex->getWidth() - hex->getWidth()/4 - 2, ind++)
	{
		if(ind % 2 != 0)
			j = hex->getHeight()/2;
		else
			j = 0;
		for(; j < windowHeight; j+= hex->getHeight() -1)
		{
		    //SDL_Texture *hexTexture = hex->generateTexture(rend->getRenderer());
			//rend->renderTexture(hexTexture, i, j);
			hex->setPosition(i, j);
			hex->draw();
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
    InputHandler::getInstance()->removeMouseClick(this);
    
    for(int i =0; i<(int)playObjects.size(); i++)
	{
		playObjects[i]->clean();
		delete playObjects[i];
    }
    
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
}

bool 
PlayState::eventInMe(SDL_Event sdlEvent)
{
	if(idSelected == "")
		return false;

	if((sdlEvent.button.x > painelRecurso->getX()) &&
        (sdlEvent.button.x < (painelRecurso->getX() + painelRecurso->getWidth())) &&
        (sdlEvent.button.y > painelRecurso->getY()) && 
        (sdlEvent.button.y < (painelRecurso->getY() + painelRecurso->getHeight())))
	{
		return false;
	}
	
	if((sdlEvent.button.x > quit->getX()) &&
        (sdlEvent.button.x < (quit->getX() + quit->getWidth())) &&
        (sdlEvent.button.y > quit->getY()) && 
        (sdlEvent.button.y < (quit->getY() + quit->getHeight())))
	{
		return false;
	}

	if( (sdlEvent.button.button == SDL_BUTTON_LEFT) &&
            (sdlEvent.button.state == SDL_RELEASED) &&
            (sdlEvent.type != SDL_MOUSEMOTION))
	{
		std::cout << "Colocando: " << idSelected << std::endl;

		int x = sdlEvent.button.x / (hex->getWidth() - hex->getWidth()/4 - 2);
        int y;
        
        if(x % 2 != 0)
            y = sdlEvent.button.y - (hex->getHeight() / 2);
        else
            y = sdlEvent.button.y;
            
        y = y / (hex->getHeight() -1);
        
        int cX = 0, cY = 0;
        int tX = 0, tY = 0;
        
        for(int i = 0, j = 0, ind = 0; (cX <= x); i+= hex->getWidth() - hex->getWidth()/4 - 2, ind++, cX++)
	    {
		    if(ind % 2 != 0)
			    j = hex->getHeight()/2;
		    else
			    j = 0;
		    
		    tX = i;
		    
		    for(; cY <= y; j+= hex->getHeight() -1, cY++)
		    {
                tY = j;
			    //rend->renderTexture(hex->generateTexture(rend->getRenderer()), i, j);
		    }
	
	    }
	    
	    if(x % 2 != 0)
	        tY += hex->getHeight()/2;

	    Image *recurso;

	    if(idSelected == "resources/img/tower.png")	
	    {
	        numTower++;
	    	//std::cout<<"Chegou aqui"<<std::endl;
	    	recurso = new Torre(tX, tY);
	    	recurso->setY(tY + recurso->getHeight() - (recurso->getHeight() / 4));	
	    	//std::cout<<"Passou aqui"<<std::endl;
	    }else{
	        recurso = new Image(idSelected, tX, tY);
	        if(idSelected == "resources/img/bomb.png")
			    numBomb++;
		    else
		        numSpy++;
	    }	
		
		recurso->setX(recurso->getX() + (recurso->getWidth() / 4));

		y = recurso->getY() + (hex->getHeight()/2) - recurso->getHeight() + 2;
		recurso->setY(y);
		
		playObjects.push_back(recurso);


		return true;
	}

	return false;
}
