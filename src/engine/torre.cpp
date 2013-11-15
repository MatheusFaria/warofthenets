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

	numInformacao  = 4;

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

	numInformacao = numInformacao*numLevelTower;
}

void
Torre::draw()
{
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width/3,
	 height/numFrames, actualRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
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
    int infoSpy = numInformacao/(5 - levelSpy);
	numInformacao -= infoSpy;
	
	return infoSpy;
}

int 
Torre::getInformacao()
{
	//std::cout<<"numInformacao"<<numInformacao<<std::endl;
	return numInformacao;
}

bool
Torre::isAliada()
{
	return tipoTorre == 0;
}