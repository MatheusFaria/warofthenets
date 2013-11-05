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


	if(bombObject != NULL)
	{
		bombObject->update();

		if(!bombObject->isAnimating())
		{
			for(int i =0; i<(int)vectorHexagon.size(); i++)
			{	
				if(vectorHexagon[i]->getBomba() != NULL )
				{
					std::cout << "i: " << i << std::endl;
					bombObject->explode(grafoHexagon, vectorHexagon[i]);
					destroyVectorObjects(bombObject->getVetorDestruicao());
					//vectorHexagon[i]->destroyGameObject();
				}	

			}

			bombObject = NULL;
		}	

	}

	/*
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
	}*/

	atualizarCronometro();
	
	if(seconds >= 15)
		finalizarTurno();

	txtNumInformation->setText(std::to_string(numInformacao));
	txtNumTower->setText(std::to_string(numTower));
	txtNumBomb->setText(std::to_string(numBomb));
	txtNumSpy->setText(std::to_string(numSpy));
	txtLevelBomb->setText(std::to_string(numLevelBomb));
	txtLevelTower->setText(std::to_string(numLevelTower));
	txtLevelSpy->setText(std::to_string(numLevelSpy));

	atualizarMapa();

}

void
PlayState::atualizarCronometro()
{
	calculateTime();	

	std::string tempo = ""; 

	if(minutes<10)
		tempo+="0";
	
	tempo+=std::to_string(minutes)+":";

	if(seconds<10)
		tempo+="0";

	tempo += std::to_string(seconds);
	txtTime->setText(tempo);

	int xseconds = painelCronometro->getX() + painelCronometro->getWidth()/2 - txtTime->getWidth()/2; 
	txtTime->setX(xseconds);
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

	/*for(int i =0; i<(int)bombObjects.size(); i++)
	{
		if(bombObjects[i] != NULL)
			bombObjects[i]->draw();
	}*/

	if(bombObject != NULL)	
		bombObject->draw();

	for(int i =0; i<(int)hudButtons.size(); i++)
		hudButtons[i]->draw();

	txtNumInformation->draw();
	txtNumTower->draw();
	txtNumBomb->draw();
	txtNumSpy->draw();
	txtTime->draw();
	txtLevelBomb->draw();
	txtLevelTower->draw();
	txtLevelSpy->draw();
}

bool
PlayState::onEnter()
{
	mapColumns = 25;
	mapRows = 15;

	windowWidth = Game::Instance()->getWindow()->getWidth();
	windowHeight =
	Game::Instance()->getWindow()->getHeight();

	bombObject = NULL;
	upgradeTower = NULL;

	iniciarTurno();

	Render::getInstance()->setColor(255, 255, 255 , 255);
	Torre::setCustoAtualizacao(5);

	idSelected = "";

	createMap();
	createHUD();
	
	numInformacao = 100;
	numTower = 0;
	numBomb = 0;
	numSpy = 0;

	numLevelTower = 1;
	numLevelBomb = 1;
	numLevelSpy = 1;

	x = 0;
	y = 0;

	velocityX = 0;
	velocityY = 0;


	InputHandler::getInstance()->addKeyboardEvent(this);


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
	

	InputHandler::getInstance()->removeKeyboardEvent(this);
		
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

	unsigned int numColumns = mapColumns;//windowWidth/75;
	unsigned int numRows = mapRows;//windowHeight/87;

	std::cout<<numColumns<<" "<<numRows<<std::endl;

	for(unsigned int i =0; i<numRows; i++)
	{	
		for(unsigned int j = 2; j<numColumns+2; j++)
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
	int espacamento = 20;

	recursoInformacao= new MenuButton(0, 0, "resources/img/paionelinformacao.png", "botaorecursoinformacao");
	int recursoInformacaoX = 0;
	int recursoInformacaoY = 0;
	recursoInformacao->setPosition(recursoInformacaoX, recursoInformacaoY);
	recursoInformacao->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoInformacao);

	recursoTower = new MenuButton(0, 0, "resources/img/botaorecursotorre.png", "botaorecursotorre", 3);
	//int recursoTowerX = levelTowerX + levelTower->getWidth() + espacamento/2;
	int recursoTowerX = recursoInformacaoX + recursoInformacao->getWidth() - recursoTower->getWidth();
	int recursoTowerY = recursoInformacaoY + espacamento + recursoInformacao->getHeight();
	recursoTower->setPosition(recursoTowerX, recursoTowerY);
	recursoTower->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoTower);

	levelTower = new Image("resources/img/botaolevel.png", 0, 0);
	int levelTowerX = recursoInformacaoX;
	int levelTowerY = recursoTowerY + recursoTower->getHeight() - levelTower->getHeight();
	levelTower->setPosition(levelTowerX, levelTowerY);

	recursoBomb = new MenuButton(0, 0, "resources/img/botaorecursobomba.png", "botaorecursobomba", 3);
	int recursoBombX = recursoTowerX;
	int recursoBombY = recursoTowerY + espacamento + recursoTower->getHeight();
	recursoBomb->setPosition(recursoBombX, recursoBombY);
	recursoBomb->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoBomb);

	levelBomb = new Image("resources/img/botaolevel.png", 0, 0);
	int levelBombX = recursoInformacaoX;
	int levelBombY = recursoBombY + recursoBomb->getHeight() - levelBomb->getHeight();
	levelBomb->setPosition(levelBombX, levelBombY);


	recursoSpy = new MenuButton(0, 0, "resources/img/botaorecursoespiao.png", "botaorecursoespiao", 3);
	int recursoSpyX = recursoTowerX;
	int recursoSpyY = recursoBombY + espacamento + recursoBomb->getHeight();
	recursoSpy->setPosition(recursoSpyX, recursoSpyY);
	recursoSpy->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(recursoSpy);

	levelSpy = new Image("resources/img/botaolevel.png",0, 0);
	int levelSpyX = recursoInformacaoX;
	int levelSpyY = recursoSpyY + recursoSpy->getHeight() - levelSpy->getHeight();
	levelSpy->setPosition(levelSpyX, levelSpyY);

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

    painelCronometro = new MenuButton(0, 0, "resources/img/painelcronometro.png", "cronometro");
    int painelCronometroX = 0;
	int painelCronometroY = windowHeight - painelCronometro->getHeight();
	painelCronometro->setPosition(painelCronometroX, painelCronometroY);
	InputHandler::getInstance()->addMouseClick(painelCronometro);
	
	//SDL_Color blackColor = {0, 0, 0, 0};
	SDL_Color whiteColor = {255, 255, 255, 0};
	
	txtNumInformation = new Text("0", 32);
	txtNumInformation->setFont(font);
    txtNumInformation->setColor(whiteColor);
    int x = recursoInformacaoX + (recursoInformacao->getWidth()/2) - (txtNumInformation->getWidth()/6);
    int y = recursoInformacaoY + (recursoInformacao->getHeight()/2) - (txtNumInformation->getHeight()/6);
    txtNumInformation->setPosition(x, y);

	txtNumTower = new Text("0", 16);
	txtNumTower->setFont(font);
    txtNumTower->setColor(whiteColor);
    x = recursoTowerX + recursoTower->getWidth() - (txtNumTower->getWidth()/4) - (espacamento/1);
    y = recursoTowerY + recursoTower->getHeight() - (txtNumTower->getHeight()/4) - (espacamento/1);
    txtNumTower->setPosition(x, y);
    
    txtNumBomb = new Text("0", 16);
	txtNumBomb->setFont(font);
    txtNumBomb->setColor(whiteColor);
    x = recursoTowerX + recursoTower->getWidth() - (txtNumBomb->getWidth()/4) - (espacamento/1);
    y = recursoBombY + recursoBomb->getHeight() - (txtNumBomb->getHeight()/4) - (espacamento/1);
    txtNumBomb->setPosition(x, y);
    
    txtNumSpy = new Text("0", 16); 
	txtNumSpy->setFont(font);
    txtNumSpy->setColor(whiteColor);
    x = recursoTowerX + recursoTower->getWidth() - (txtNumSpy->getWidth()/4) - (espacamento/1);
    y = recursoSpyY + recursoSpy->getHeight() - (txtNumSpy->getHeight()/4) - (espacamento/1);
    txtNumSpy->setPosition(x, y);

	txtTime = new Text("00:00", 50);
	txtTime->setFont(font);
	txtTime->setColor(whiteColor);
	x =  painelCronometroX + painelCronometro->getWidth()/2 - txtTime->getWidth()/2;
	y = painelCronometroY + painelCronometro->getHeight()/2 - txtTime->getHeight()/2;
	txtTime->setPosition(x,y);

	txtLevelBomb = new Text("1", 28);
	txtLevelBomb->setFont(font);
    txtLevelBomb->setColor(whiteColor);
    x = levelBombX + levelBomb->getWidth()/2 - txtLevelBomb->getWidth()/2;
    y = levelBombY + levelBomb->getHeight()/2 - txtLevelBomb->getHeight()/2;
    txtLevelBomb->setPosition(x, y);

    txtLevelTower = new Text("1", 28);
	txtLevelTower->setFont(font);
    txtLevelTower->setColor(whiteColor);
    x = levelTowerX + levelTower->getWidth()/2 - txtLevelTower->getWidth()/2;
    y = levelTowerY + levelTower->getHeight()/2 - txtLevelTower->getHeight()/2;
    txtLevelTower->setPosition(x, y);

    txtLevelSpy = new Text("1", 28);
	txtLevelSpy->setFont(font);
    txtLevelSpy->setColor(whiteColor);
    x = levelSpyX + levelSpy->getWidth()/2 - txtLevelSpy->getWidth()/2;
    y = levelSpyY + levelSpy->getHeight()/2 - txtLevelSpy->getHeight()/2;
    txtLevelSpy->setPosition(x, y);

    hudBackground = new Image("resources/img/hud_bg.png", 0, 0);

    upgradeTower = new MenuButton(0,0,"resources/img/buttonupgrade.png", "buttonupgrade", 3);
    x = levelTowerX;
    y = levelTowerY - upgradeTower->getHeight() -espacamento/4;
    upgradeTower->setPosition(x,y);
	upgradeTower->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(upgradeTower);

    upgradeBomb = new MenuButton(0,0,"resources/img/buttonupgrade.png", "buttonupgrade", 3);
    x = levelBombX;
    y = levelBombY - upgradeBomb->getHeight() -espacamento/4;
    upgradeBomb->setPosition(x,y);
	upgradeBomb->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(upgradeBomb);

    upgradeSpy = new MenuButton(0,0,"resources/img/buttonupgrade.png", "buttonupgrade", 3);
    x = levelSpyX;
    y = levelSpyY - upgradeSpy->getHeight() -espacamento/4;
    upgradeSpy->setPosition(x,y);
	upgradeSpy->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(upgradeSpy);


	hudButtons.push_back(upgradeTower);
	hudButtons.push_back(recursoTower);
	hudButtons.push_back(upgradeBomb);
	hudButtons.push_back(recursoBomb);
	hudButtons.push_back(upgradeSpy);
	hudButtons.push_back(recursoSpy);
	hudButtons.push_back(quit);
	hudButtons.push_back(fimTurno);
	hudButtons.push_back(recursoInformacao);
	hudButtons.push_back(painelCronometro);


    playObjects.push_back(hudBackground);
    playObjects.push_back(levelTower);
    playObjects.push_back(levelBomb);
   	playObjects.push_back(levelSpy);
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

    if(mouseClick == upgradeTower)
    {
    	if(towerActualized)
    		return;

    	if(Torre::getCustoAtualizacao()<=numInformacao && numLevelTower < 3)
    	{
	    	recursoTower->incCurrentRow();
	    	numLevelTower++;
	    	numInformacao -= Torre::getCustoAtualizacao();
	    	upgradeTower->incCurrentRow();

	    	atualizarTorres();
	    	towerActualized = true;
	    }	
    }

}

GameObject*
PlayState::createObject(Hexagon *hex)
{
	Image* recurso = NULL;

	if(idSelected =="")
		return NULL;
	if(idSelected == "resources/img/tower.png"  && canConstruct(hex))
    	recurso = new Torre(numLevelTower);
	else if(idSelected == "resources/img/bomb.png" && bombObject == NULL)
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

	if(object == NULL)
		return;
	else
	{
		if(dynamic_cast<Bomba*>(object))
		{
			if(numInformacao >= 2)
			{
				bombObject = (Bomba*) object;
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
	if(upgradeTower != NULL && upgradeTower->getCurrentRow()==1)
	{
		if(numLevelTower == 2)
				upgradeTower->decCurrentRow();
		else if(numLevelTower == 3)	
				upgradeTower->incCurrentRow();

	}

	towerActualized = false;
	bombActualized = false;
	spyActualized = false;

	actualTime = SDL_GetTicks();	
}

void 
PlayState::atualizarTorres()
{
	for(unsigned int i =0; i<playObjects.size(); i++)
	{
		if(dynamic_cast<Torre*>(playObjects[i]))
			((Torre*)playObjects[i])->incActualColumn();
	}
}

void 
PlayState::atualizarMapa()
{
	int hexagonX;
	int hexagonY;

	if(this->velocityX == 0 && this->velocityY ==0)
		return;

	//std::cout<<"this->x : "<<this->x<<std::endl;
	if(this->velocityX<0)
	{
		if(this->x + this->velocityX < 0)	
			this->velocityX =0;
	}
	else
	{
		if(this->x + windowWidth > (mapColumns * 75))
			this->velocityX = 0;
	}

	
	if(this->velocityY<0)
	{
		if(this->y + this->velocityY < 0) 
			this->velocityY=0;
	}
	else
	{
		if(this->y + windowHeight > (mapRows * 87) + 44)
			this->velocityY=0;
	}

	this->x = (this->x + this->velocityX);
	this->y = (this->y + this->velocityY);

	for(int i =0; i<(int)vectorHexagon.size(); i++)
	{
		//hexagonX = vectorHexagon[i]->getX() + this->x;
		//hexagonY = vectorHexagon[i]->getY() + this->y;

		hexagonX = vectorHexagon[i]->getX() - this->velocityX;
		hexagonY = vectorHexagon[i]->getY() - this->velocityY;

		//if( (hexagonX >= 0) && (hexagonX <= (mapColumns * 75)) )
			vectorHexagon[i]->setX(hexagonX);

		//if( (hexagonY >= 0) && (hexagonY < (mapRows * 87)))
			vectorHexagon[i]->setY(hexagonY);
	}
}

bool 
PlayState::eventInMe(SDL_Event sdlEvent)
{
	int velocity = 10;

	
	if(sdlEvent.key.keysym.sym == SDLK_UP)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityY = -velocity;
		else
			velocityY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_DOWN)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityY = +velocity;
		else
			velocityY = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_LEFT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityX = -velocity;
		else
			velocityX = 0;
	}

	if(sdlEvent.key.keysym.sym == SDLK_RIGHT)
	{
		if(sdlEvent.key.state == SDL_PRESSED)
			velocityX = +velocity;
		else
			velocityX = 0;
	}

	return true;
}
