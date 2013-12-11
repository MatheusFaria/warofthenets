
#include "spy.h"
#include "SDL2/SDL.h"
#include "texturemanager.h"
#include "render.h"
#include "soundmanager.h"
#include <iostream>

using namespace std;

std::string Spy::path = "resources/img/spy.png";
int Spy::custoUnidade = 0;
int Spy::custoAtualizacao = 0;

Spy::Spy(int numLevelSpy, int x, int y):Image(path,x,y)
{
	this->numLevelSpy = numLevelSpy;
	this->numInformacao = 0;
	this->numFrames = 4;
	actualRow = 1;
	currentFrame = numLevelSpy - 1;
	//currentFrame = 0;

	playSound();
}

void 
Spy::playSound()
{
	SoundManager::Instance()->playSound("spy", 0);
}


void
Spy::update()
{
	int intervalo = 100;
	actualRow = (SDL_GetTicks()/intervalo)%numFrames;
}

void
Spy::draw()
{
	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width/3,
	 height/numFrames, actualRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

int
Spy::getCustoAtualizacao()
{
	return Spy::custoAtualizacao;
}

void 
Spy::setCustoAtualizacao(int _custoAtualizacao)
{
	Spy::custoAtualizacao = _custoAtualizacao;
}

int
Spy::getCustoUnidade()
{
	return Spy::custoUnidade;
}

void 
Spy::setCustoUnidade(int _custoUnidade)
{
	Spy::custoUnidade = _custoUnidade;
}

void 
Spy::setNumLevel(int numLevel)
{
    this->numLevelSpy = numLevel;
    
}

void
Spy::incActualColumn()
{
	currentFrame++;
}


int
Spy::getLevel()
{
	return numLevelSpy;
}

void
Spy::setNumInformacao(int numInfo)
{
    this->numInformacao = numInfo;
}

int
Spy::getInformacao() const
{   
    return this->numInformacao;
}

