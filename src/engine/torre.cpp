#include "torre.h"
#include "SDL2/SDL.h"
#include "texturemanager.h"
#include "render.h"
#include "soundmanager.h"
#include <iostream>

int Torre::custoAtualizacao = 0;
int Torre::custoUnidade = 0;
int Torre::ALIADA = 0;
int Torre::INIMIGA = 1;

Torre::Torre(int tipoTorre, int numLevelTower, int x, int y, std::string path):Image(path,x,y)
{
	this->tipoTorre = tipoTorre;
	this->numFrames = 4;
	actualRow = 1;
	this->numLevels =3;
	this->numLevelTower = numLevelTower;
	currentFrame = numLevelTower - 1;

	numInformacao = 4;
	
	imageAliada = new Image("resources/img/hexagonovermelho.png", 0, 0);

	playSound();
}

bool 
Torre::playSound()
{	
	SoundManager::Instance()->playSound("torre", 0);
	return true;
}

void
Torre::update()
{
	int intervalo = 100;
	actualRow = (SDL_GetTicks()/intervalo)%numFrames;
}

void 
Torre::setPosition(int x, int y)
{
    int imageAliadaX = x + (getWidth()/6) - (imageAliada->getWidth()/2);
    int imageAliadaY = y + (getHeight()/4) - (imageAliada->getHeight()/2);    
    
    SDLGameObject::setPosition(x, y);
    imageAliada->setPosition(imageAliadaX, imageAliadaY);    
}

void 
Torre::clean()
{
    imageAliada->clean();
    delete imageAliada;
}

void
Torre::draw()
{    
    if(isAliada())
        imageAliada->draw();
    
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width/3,
	 height/numFrames, actualRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

int 
Torre::getNumLevel()
{
    return numLevelTower;
}

void 
Torre::setNumLevel(int numLevel)
{
    this->numLevelTower = numLevel;
    this->numInformacao = 4 * numLevelTower;
}

int
Torre::getCustoAtualizacao()
{
	return Torre::custoAtualizacao;
}

void 
Torre::setCustoAtualizacao(int _custoAtualizacao)
{
	Torre::custoAtualizacao = _custoAtualizacao;
}

int
Torre::getCustoUnidade()
{
	return Torre::custoUnidade;
}

void 
Torre::setCustoUnidade(int _custoUnidade)
{
	Torre::custoUnidade = _custoUnidade;
}

void
Torre::incActualColumn()
{
	currentFrame++;
}

int
Torre::spyOnTower(int levelSpy)
{
    int infoSpy = levelSpy * numLevelTower;
	numInformacao = (numLevelTower * 4) - infoSpy;
	
	return infoSpy;
}

void 
Torre::removeSpy()
{
    numInformacao = (numLevelTower * 4);
}

int 
Torre::getInformacao()
{
	return numInformacao;
}

bool
Torre::isAliada()
{
	return tipoTorre == 0;
}
