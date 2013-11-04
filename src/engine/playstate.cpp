#include "playstate.h"
#include "gameoverstate.h"
#include "render.h"
#include "game.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"
#include "torre.h"
#include "bomba.h"
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

	for(int i =0; i<(int)hudButtons.size(); i++)
		hudButtons[i]->update();

	

	std::vector<Bomba*> bombDelete;

	for(int i =0; i<(int)bombObjects.size(); i++)
	{
		bombObjects[i]->update();
		//std::cout << "bombObjects[i]->isAnimating(): " << bombObjects[i]->isAnimating() << std::endl;
		if(!bombObjects[i]->isAnimating())
		{
			bombDelete.push_back(bombObjects[i]);
		}
	}


	std::vector<Bomba*>::iterator it;
	for(int i =(int)bombDelete.size()-1; i>=0; i--)
	{
		Bomba *bomba = bombDelete[i];
		it = find(bombObjects.begin(), bombObjects.end(), bomba);
		bombObjects.erase(it);

		//std::cout<<vectorHexagon.size()<<std::endl;

		for(int i =0; i<(int)vectorHexagon.size(); i++)
		{
			if(vectorHexagon[i]->getBomba() != NULL )
			{
				std::cout << "i: " << i << std::endl;
				bomba->explode(grafoHexagon, vectorHexagon[i]);
				destroyVectorObjects(bomba->getVetorDestruicao());
				//vectorHexagon[i]->destroyGameObject();
			}	

		}
	}

	calculateTime();
	
	if(seconds >= 5)
		finalizarTurno();

	txtNumInformation->setText(std::to_string(numInformacao));
	txtNumTower->setText(std::to_string(numTower));
	txtNumBomb->setText(std::to_string(numBomb));
	txtNumSpy->setText(std::to_string(numSpy));
	txtTime->setText(std::to_string(minutes)+":"+std::to_string(seconds));

}

void 
PlayState::calculateTime()
{
	int tempo = SDL_GetTicks() - actualTime;

	minutes = tempo/60000;
	tempo -= minutes*60000;

	seconds = tempo/1000;
}

void
PlayState::render()
{
	//createMap();
	
	for(int i =0; i<(int)vectorHexagon.size(); i++)
		vectorHexagon[i]->draw();

	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->draw();

	for(int i =0; i<(int)bombObjects.size(); i++)
		bombObjects[i]->draw();

	for(int i =0; i<(int)hudButtons.size(); i++)
		hudButtons[i]->draw();

	txtNumInformation->draw();
	txtNumTower->draw();
	txtNumBomb->draw();
	txtNumSpy->draw();
	txtTime->draw();
}

bool
PlayState::onEnter()
{
	windowWidth = Game::Instance()->getWindow()->getWidth();
	windowHeight =
	Game::Instance()->getWindow()->getHeight();

	iniciarTurno();

	Render::getInstance()->setColor(255, 255, 255 , 255);
	

	idSelected = "";

	createMap();
	createHUD();
	
	numInformacao = 1;
	numTower = 0;
	numBomb = 0;
	numSpy = 0;
	iniciarTurno();

	std::cout<<"Play State"<<std::endl;
	return true;
}


bool 
PlayState::onExit()
{

    for(int i =0; i<(int)playObjects.size(); i++)
	{
		playObjects[i]->clean();
		delete playObjects[i];
    }
    

    for(int i =0; i<(int)vectorHexagon.size(); i++)
    {	
    	InputHandler::getInstance()->removeMouseClick(vectorHexagon[i]);
		delete vectorHexagon[i];
	}

	for(int i =0; i<(int)hudButtons.size(); i++)
    {	
    	InputHandler::getInstance()->removeMouseClick(hudButtons[i]);
		delete hudButtons[i];
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
            foundAdjacents(hex);
		}
	}	
}

void
PlayState::foundAdjacents(Hexagon *hex)
{
    //std::cout << "\n\nfoundAdjacents: " << std::endl;

	vector<Hexagon *> adjacents;

	int width = 100;
	int height = 87;
	int centerX = hex->getX() + (width/2);
	int centerY = hex->getY() + (height/2);

	int x;
	int y;

	for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	{
	    //CIMA
		x = centerX;
		y = centerY - height;
		if(vectorHexagon[i]->isMyCoordinate(x, y))
		{
			adjacents.push_back(vectorHexagon[i]);
			grafoHexagon[vectorHexagon[i]].push_back(hex);
		}
		
		//CIMA + ESQUERDA
		x = centerX - (width/2);
		y = centerY - (height/2);
		if(vectorHexagon[i]->isMyCoordinate(x, y))
		{
			adjacents.push_back(vectorHexagon[i]);
			grafoHexagon[vectorHexagon[i]].push_back(hex);
		}
		
		//CIMA + DIREITA
		x = centerX + (width/2);
		y = centerY - (height/2);
		if(vectorHexagon[i]->isMyCoordinate(x, y))
		{
			adjacents.push_back(vectorHexagon[i]);
			grafoHexagon[vectorHexagon[i]].push_back(hex);
		}
		
		//BAIXO
		x = centerX;
		y = centerY + height;
		if(vectorHexagon[i]->isMyCoordinate(x, y))
		{
			adjacents.push_back(vectorHexagon[i]);
			grafoHexagon[vectorHexagon[i]].push_back(hex);
		}
		
		//BAIXO + ESQUERDA
		x = centerX - (width/2);
		y = centerY + (height/2);
		if(vectorHexagon[i]->isMyCoordinate(x, y))
		{
			adjacents.push_back(vectorHexagon[i]);
			grafoHexagon[vectorHexagon[i]].push_back(hex);
		}
		
		//BAIXO + DIREITA
		x = centerX + (width/2);
		y = centerY + (height/2);
		if(vectorHexagon[i]->isMyCoordinate(x, y))
		{
			adjacents.push_back(vectorHexagon[i]);
			grafoHexagon[vectorHexagon[i]].push_back(hex);
		}
	}

	grafoHexagon[hex] = adjacents;
}

bool 
PlayState::canConstruct(Hexagon *hex)
{
    vector<Hexagon *> adjacents;
    adjacents = grafoHexagon[hex];

    vector<Hexagon *> adjacentsAdj;
    
    //std::cout << "adjacents.size(): " << adjacents.size() << std::endl;
    bool temTorre = false;
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
    {
    	if(vectorHexagon[i]->haveObject())
    		temTorre = true;
    }

    if(!temTorre)
    	return true;

    for(unsigned int i = 0; i < adjacents.size(); i++)
    {
        //std::cout << "adjacents[i]->haveObject(): " << adjacents[i]->haveObject() << std::endl;
        if(dynamic_cast<Torre *>(adjacents[i]->getObject()))
    	{
	        if(adjacents[i]->haveObject())
	            return false;
        }
    }

    for(unsigned int i = 0; i < adjacents.size(); i++)
    {
		adjacentsAdj = grafoHexagon[adjacents[i]];

    	for(unsigned int i = 0; i < adjacentsAdj.size(); i++)
    	{
			if(adjacentsAdj[i]->haveObject())
				return true;
		}
	}

    
    return false;
}

void 
PlayState::createHUD()
{

	std::string font = "resources/font/Army.ttf";

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

	recursoInformacao= new MenuButton(0, 0, "resources/img/paionelinformacao.png", "botaorecursoinformacao");
	int recursoInformacaoX = painelRecurso->getX() + painelRecurso->getWidth();
	int recursoInformacaoY = windowHeight - recursoInformacao->getHeight();
	recursoInformacao->setPosition(recursoInformacaoX, recursoInformacaoY);
	recursoInformacao->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoInformacao);
	
	quit = new MenuButton(0, 0, "resources/img/botaosair.png", "botaosair");
	int quitX = windowWidth - quit->getWidth();
	int quitY = 0;
	quit->setPosition(quitX, quitY);
	quit->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(quit);

	fimTurno = new MenuButton(0, 0, "resources/img/botaoFimTurno.png", "botaofimturno");
	int fimTurnoX = windowWidth - fimTurno->getWidth();
	int fimTurnoY = windowHeight - fimTurno->getHeight();
	fimTurno->setPosition(fimTurnoX, fimTurnoY);
	fimTurno->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(fimTurno);
	
	SDL_Color blackColor = {0, 0, 0, 0};
	
	txtNumInformation = new Text("0", 32);
	txtNumInformation->setFont(font);
    txtNumInformation->setColor(blackColor);
    int x = recursoInformacaoX + (recursoInformacao->getWidth()/2) - (txtNumInformation->getWidth()/6);
    int y = recursoInformacaoY + (recursoInformacao->getHeight()/2) - (txtNumInformation->getHeight()/6);
    txtNumInformation->setPosition(x, y);

	txtNumTower = new Text("0", 16);
	txtNumTower->setFont(font);
    txtNumTower->setColor(blackColor);
    x = recursoTowerX + recursoTower->getWidth() - txtNumTower->getWidth() - 18;
    y = recursoTowerY + recursoTower->getHeight() - txtNumTower->getHeight() - 9;
    txtNumTower->setPosition(x, y);
    
    txtNumBomb = new Text("0", 16);
	txtNumBomb->setFont(font);
    txtNumBomb->setColor(blackColor);
    x = recursoTowerX + recursoTower->getWidth() - txtNumBomb->getWidth() - 18;
    y = recursoBombY + recursoBomb->getHeight() - txtNumBomb->getHeight() - 9;
    txtNumBomb->setPosition(x, y);
    
    txtNumSpy = new Text("0", 16); 
	txtNumSpy->setFont(font);
    txtNumSpy->setColor(blackColor);
    x = recursoTowerX + recursoTower->getWidth() - txtNumSpy->getWidth() - 18;
    y = recursoSpyY + recursoSpy->getHeight() - txtNumSpy->getHeight() - 9;
    txtNumSpy->setPosition(x, y);

    painelCronometro = new MenuButton(0, 0, "resources/img/painelcronometro.png", "cronometro");
	InputHandler::getInstance()->addMouseClick(painelCronometro);

	txtTime = new Text("00:00", 16);
	txtTime->setFont(font);
	txtTime->setColor(blackColor);
	x = painelCronometro->getWidth()/2 - txtTime->getWidth()/2;
	y = painelCronometro->getHeight()/2 - txtTime->getHeight()/2;
	txtTime->setPosition(x,y);

	hudButtons.push_back(painelRecurso);
	hudButtons.push_back(recursoTower);
	hudButtons.push_back(recursoBomb);
	hudButtons.push_back(recursoSpy);
	hudButtons.push_back(quit);
	hudButtons.push_back(fimTurno);
	hudButtons.push_back(recursoInformacao);
	hudButtons.push_back(painelCronometro);


}

void 
PlayState::onMouseClick(MouseClick *mouseClick)
{
	if(mouseClick == recursoTower)
	{
		idSelected = "resources/img/tower.png";

		std::cout << "Selecionou: TORRE" << std::endl;
		return;
	}

	if(mouseClick == recursoBomb)
	{
		idSelected = "resources/img/bomb.png";

		std::cout << "Selecionou: BOMBA" << std::endl;
		return;
	}

	if(mouseClick == recursoSpy)
	{
		idSelected = "resources/img/spy.png";

		std::cout << "Selecionou: ESPIAO" << std::endl;
		return;
	}
	
	if(mouseClick == quit)
	{
	    Game::Instance()->getStateMachine()->changeState(new GameOverState());
		return;
    }

    if(dynamic_cast<Hexagon*>(mouseClick))
    {

    	std::cout<<"Clicou no Hexagon"<<std::endl;
    	Hexagon *temp = (Hexagon *) mouseClick;

    	//std::cout<<"temp->haveObject(): " << temp->haveObject() <<std::endl;


    	if(temp->isMouseLeft())
    		showObject(temp);
    	else if(temp->isMouseRight())
    	{
    		std::cout<<"Clicou no direito"<<std::endl;
    		deleteObject(temp);	
    	}	

    	return;	
    }

    if(mouseClick == fimTurno)
    {
    	std::cout<<"Fim turno!"<<std::endl;
    	finalizarTurno();
    }

}

GameObject*
PlayState::createObject(Hexagon *hex)
{
	Image* recurso = NULL;

	if(idSelected =="")
		return NULL;
	if(idSelected == "resources/img/tower.png"  && canConstruct(hex))
    	recurso = new Torre();
	else if(idSelected == "resources/img/bomb.png")
	{
		recurso = new Bomba(hex->getX(), hex->getY());
	}		
	else if(idSelected == "resources/img/spy.png")
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
	std::cout<<"Entrou aqui"<<std::endl;

	if(dynamic_cast<Torre*>(object))
		numTower--;
	else if(dynamic_cast<Bomba*>(object))
		numBomb--;
}

void 
PlayState::showObject(Hexagon* hex)
{
	GameObject* object = createObject(hex);

	if(!object)
		return;
	else
	{
		if(dynamic_cast<Bomba*>(object))
		{
			if(numInformacao >= 2)
			{
				bombObjects.push_back((Bomba*)object);
				hex->setObject(object);
				incObject();
				numInformacao -= 2;
			}
		}		
		else if(dynamic_cast<Torre*>(object)) 
		{
			if(numInformacao >= 1)
			{
				if(hex->setObject(object))
				{
					playObjects.push_back(object);
					incObject();
					numInformacao -= 1;
				}
			}
		}
		else //Se for espiao
		{
			if(numInformacao >= 3)
			{
				if(hex->setObject(object))
				{
					playObjects.push_back(object);
					incObject();
					numInformacao -= 3;
				}
			}
		}

			
					
	}
}

void
PlayState::deleteObject(Hexagon *hex)
{

	GameObject* object = hex->getObject();

	if(object != NULL)
	{

		vector<GameObject*>::iterator it;

		it = find(playObjects.begin(), playObjects.end(), object);

		if(it != playObjects.end())
			playObjects.erase(it);

		decObject(object);
		delete object;

	}
	
	GameObject* bomba = hex->getBomba();

	if(bomba!= NULL)
	{
		decObject(bomba);	
		delete bomba;
	}	


	hex->destroyGameObject();
		
}

void
PlayState::destroyVectorObjects(std::vector<Hexagon*> destroy)
{
	std::cout << "destroy.size(): " << destroy.size() << std::endl;
	for(unsigned int i =0; i<destroy.size();i++)
		deleteObject(destroy[i]);
}

void 
PlayState::finalizarTurno()
{
	if(numTower > 0)
		numInformacao += numTower * 2;
	else
		numInformacao++;

	iniciarTurno();
}


void
PlayState::iniciarTurno()
{
	actualTime = SDL_GetTicks();	
}