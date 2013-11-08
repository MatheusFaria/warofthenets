#include "playstate.h"
#include "gameoverstate.h"
#include "render.h"
#include "game.h"
#include "SDL2/SDL.h"
#include "inputhandler.h"
#include "torre.h"
#include "bomba.h"
#include "spy.h"
#include "networkmanager.h"
#include <algorithm>
#include <iostream>

#define TOWER 10
#define BOMB 20
#define SPY 10

const std::string PlayState::playId = "PLAY";

void
PlayState::update()
{

	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->update();

	for(int i =0; i<(int)vectorEnemyObjects.size(); i++)
		vectorEnemyObjects[i]->update();

	for(int i =0; i<(int)hudImages.size(); i++)
		hudImages[i]->update();

	for(int i =0; i<(int)hudButtons.size(); i++)
		hudButtons[i]->update();

    hexagonMap->update();

	if(bombObject != NULL)
	{
		bombObject->update();

		if(!bombObject->isAnimating())
		{
		    std::vector<Hexagon*> vectorHexagon;
		    
		    vectorHexagon = hexagonMap->getVectorHexagon();
		    
			for(int i =0; i<(int)vectorHexagon.size(); i++)
			{	
				if(vectorHexagon[i]->getBomba() != NULL )
				{
					std::cout << "i: " << i << std::endl;
					bombObject->explode(hexagonMap->getGrafoHexagon(), vectorHexagon[i]);
					destroyVectorObjects(bombObject->getVetorDestruicao());
					//vectorHexagon[i]->destroyGameObject();
				}	

			}

			bombObject = NULL;
		}	
	}

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
	
	if(!isMyTurn)
		receberMensagens();

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
	for(int i =0; i<(int)playObjects.size(); i++)
		playObjects[i]->draw();

	for(int i =0; i<(int)vectorEnemyObjects.size(); i++)
		vectorEnemyObjects[i]->draw();

    hexagonMap->draw();

	if(bombObject != NULL)	
		bombObject->draw();

	for(int i =0; i<(int)hudImages.size(); i++)
		hudImages[i]->draw();

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
    
    hexagonMap = new HexagonMap(mapColumns, mapRows);
    hexagonMap->setEventListener(this);
    hexagonMap->update();
    hexagonMap->draw();
    
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

	if(NetworkManager::Instance()->tipo == 0)
	{
		isMyTurn = true;
		ativarBotoes(true);
	}
	else
	{
		isMyTurn = false;
		ativarBotoes(false);
	}


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

    for(int i =0; i<(int)vectorEnemyObjects.size(); i++)
	{
		vectorEnemyObjects[i]->clean();
		delete vectorEnemyObjects[i];
	}

	for(int i =0; i<(int)hudImages.size(); i++)
	{
		hudImages[i]->clean();
		delete hudImages[i];
    }

	for(int i =0; i<(int)hudButtons.size(); i++)
    {	
    	InputHandler::getInstance()->removeMouseClick(hudButtons[i]);
		delete hudButtons[i];
	}

    hexagonMap->clean();
    delete hexagonMap;

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


	hudImages.push_back(hudBackground);
	hudImages.push_back(levelTower);
	hudImages.push_back(levelBomb);
	hudImages.push_back(levelSpy);
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
        std::cout<<"isMyTurn = " << isMyTurn <<std::endl;
        
        if(!isMyTurn)
            return;
            
    	std::cout<<"Clicou no Hexagon"<<std::endl;
    	Hexagon *temp = (Hexagon *) mouseClick;

    	if(temp->getX() + temp->getWidth() < hudBackground->getWidth())
    		return;

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
	if(idSelected == "resources/img/tower.png"  && hexagonMap->canConstruct(hex))
    	recurso = new Torre(numLevelTower);
	else if(idSelected == "resources/img/bomb.png" && bombObject == NULL)
	{
		recurso = new Bomba(hex->getX(), hex->getY());
	}		
	else if(idSelected == "resources/img/spy.png")
        recurso = new Spy();
	

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
	else
		numSpy--;
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
			criarBomba(hex, (Bomba *)object);
		}		
		else if(dynamic_cast<Torre*>(object)) 
		{
			criarTorre(hex, (Torre *)object);
		}
		else if(dynamic_cast<Spy*>(object)) 
		{
			criarEspiao(hex, (Spy *)object);
		}

			
					
	}
}

void 
PlayState::criarTorre(Hexagon *hex, Torre *tower)
{
	if(numInformacao >= 1)
	{
		if(hex->setObject(tower))
		{
			playObjects.push_back(tower);
			incObject();
			numInformacao -= 1;
		}
	}

	Data data;

	data.x = hex->getX()+50;
	data.y = hex->getY()+43;
	data.type = TOWER + numLevelTower;

	NetworkManager::Instance()->sendMessage(data);
}

void 
PlayState::criarTorreInimiga(Data data)
{
	Hexagon* hex = encontrarHexagono(data.x, data.y);

	Torre *tower = new Torre(data.type%10);
	

	hex->setObject(tower);
	vectorEnemyObjects.push_back(tower);
}

void 
PlayState::criarBomba(Hexagon *hex, Bomba *bomba)
{
	if(numInformacao >= 2)
	{
		bombObject = bomba;
		hex->setObject(bomba);
		incObject();
		numInformacao -= 2;
	}
	
	Data data;
	
	data.x = hex->getX()+50;
	data.y = hex->getY()+43;
	data.type = BOMB + numLevelBomb;

	NetworkManager::Instance()->sendMessage(data);
}

void
PlayState::criarBombaInimiga(Data data)
{
    Hexagon* hex = encontrarHexagono(data.x, data.y);
    
    Bomba *bomb = new Bomba(hex->getX(), hex->getY());
    
    hex->setObject(bomb);
    bombObject = bomb;
}

void 
PlayState::criarEspiao(Hexagon *hex, Spy *spy)
{
	if(numInformacao >= 3)
	{
		if(hex->setObject(spy))
		{
			playObjects.push_back(spy);
			incObject();
			numInformacao -= 3;
		}
	}
	
	Data data;
	
	data.x = hex->getX()+50;
	data.y = hex->getY()+43;
	data.type = SPY + numLevelSpy;
	
	NetworkManager::Instance()->sendMessage(data);
}

void
PlayState::criarEspiaoInimiga(Data data)
{
    Hexagon* hex = encontrarHexagono(data.x, data.y);

	Spy *spy = new Spy();
	
	hex->setObject(spy);
	vectorEnemyObjects.push_back(spy);
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
				
		it = find(vectorEnemyObjects.begin(), vectorEnemyObjects.end(), object);
		
		if(it != vectorEnemyObjects.end())
			vectorEnemyObjects.erase(it);

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
    if(!isMyTurn)
        return;
        
    std::cout << "Finalizando turno" << std::endl;
	ativarBotoes(false);

	for(unsigned int i =0; i<playObjects.size();i++)
	{
		if(dynamic_cast<Torre*>(playObjects[i]))
		{
			std::cout<<"Entrou aqui"<<std::endl;
			numInformacao+=((Torre*)playObjects[i])->getInformacao();
		}	
	}

	Data data;
	data.type = 40;
	NetworkManager::Instance()->sendMessage(data);
	
	actualTime = SDL_GetTicks();
	isMyTurn = false;

	//iniciarTurno();
}


void
PlayState::iniciarTurno()
{
    if(isMyTurn)
        return;
        
    std::cout << "Iniciando turno" << std::endl;
    isMyTurn = true;
    
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

	ativarBotoes(true);	
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
    int newX;
	int newY;
	
	if(this->velocityX == 0 && this->velocityY ==0)
	{	    
	    hexagonMap->setVelocityX(velocityX);
	    hexagonMap->setVelocityY(velocityY);
	    
		return;
    }
    
	//std::cout<<"this->x : "<<this->x<<std::endl;
	if(this->velocityX<0)
	{
		if(this->x + this->velocityX < 0)	
			this->velocityX = 0;
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

    if(bombObject != NULL)
    {
        newX = bombObject->getX() - this->velocityX;
        newY = bombObject->getY() - this->velocityY;
        
        bombObject->setPosition(newX, newY);
    }

	this->x = (this->x + this->velocityX);
	this->y = (this->y + this->velocityY);
	
	hexagonMap->setVelocityX(velocityX);
	hexagonMap->setVelocityY(velocityY);
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

void
PlayState::receberMensagens()
{
	Data data;

	while(true)
	{
		data = NetworkManager::Instance()->receiveMessage();

		if(data.type == -1)
			break;

        std::cout << "\nreceberMensagens: " << data.x << std::endl;    
        std::cout << "data.type: " << data.type << std::endl;   
        std::cout << "data.x: " << data.x << std::endl;
        std::cout << "data.y: " << data.y << std::endl<< std::endl;

		parseData(data);
	}
}

void
PlayState::parseData(Data data)
{
    
	int unidade = data.type/10;

	if(unidade == 4)
		iniciarTurno();

	else if(unidade == TOWER/10)
		criarTorreInimiga(data);
	
	else if(unidade == BOMB/10)
	    criarBombaInimiga(data);
	
	else if(unidade == SPY/10)
	    criarEspiaoInimiga(data);
}

Hexagon * 
PlayState::encontrarHexagono(int x, int y)
{
	std::vector<Hexagon*> vectorHexagon = hexagonMap->getVectorHexagon();

	for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	{
		if(vectorHexagon[i]->isMyCoordinate(x, y))
			return vectorHexagon[i];
	}
	
	std::cout << "HEXAGONO NULO!" << std::endl;

	return NULL;
}

void 
PlayState::ativarBotoes(bool comando)
{
	for(unsigned int i =0; i<hudButtons.size();i++)
		hudButtons[i]->setActive(comando);

}
