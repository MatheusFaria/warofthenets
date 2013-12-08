#include "bomba.h"
#include "SDL2/SDL.h"
#include "texturemanager.h"
#include "render.h"
#include "base.h"
#include "soundmanager.h"
#include <iostream>
#include <math.h>


std::string Bomba::path = "resources/img/bomb.png";
int Bomba::custoUnidade = 0;
int Bomba::custoAtualizacao = 0;
int Bomba::actualRow = 0;

Bomba::Bomba(int numLevel, int x, int y):Image(path,x,y)
{
	numFrames = 5;
	currentFrame = 1;
	
	this->numLevel = numLevel;

	this->raioDestruicao = 6 /* * pow( (2 + 1), (raioDestruicao - 1) )*/ ;
	Bomba::actualRow = numLevel-1;

	playExploiveSound();
	
	//animate();

	tempInicial = SDL_GetTicks();
	inAnimate = true;



}

bool 
Bomba::playExploiveSound()
{
	if(numLevel == 1)
		SoundManager::Instance()->playSound("bomba1", 0);
	else if(numLevel == 2)
		SoundManager::Instance()->playSound("bomba2", 0);
	else
		SoundManager::Instance()->playSound("bomba3", 0);

	return true;
}

void
Bomba::update()
{
	int intervalo = 200;

	int delta= SDL_GetTicks() - tempInicial;

	if(delta >= intervalo)
	{
		currentFrame++;
		tempInicial = SDL_GetTicks();
	}

	
	if(currentFrame == 5)
		inAnimate = false;

	/*int temp = SDL_GetTicks() - tempInicial;

	if(temp > 1500)
		inAnimate = false;*/
}

bool 
Bomba::isAnimating()
{
	return inAnimate;
}

void
Bomba::draw()
{

	TextureManager::Instance()->drawFrame(imageId, (Uint32)position.getX(),(Uint32)position.getY(),width/5,
	 height/3, Bomba::actualRow, currentFrame,Render::getInstance()->getRenderer(), 0 );
}

int
Bomba::getCustoAtualizacao()
{
	return Bomba::custoAtualizacao;
}

void 
Bomba::setCustoAtualizacao(int _custoAtualizacao)
{
	Bomba::custoAtualizacao = _custoAtualizacao;
}

int
Bomba::getCustoUnidade()
{
	return Bomba::custoUnidade;
}

void 
Bomba::setCustoUnidade(int _custoUnidade)
{
	Bomba::custoUnidade = _custoUnidade;
}

void
Bomba::incActualColumn()
{
	Bomba::actualRow++;
}


void 
Bomba::explode(map<Hexagon*, vector<Hexagon*>>  grafoHexagon, Hexagon *hex)
{
	mapaVisitado.clear();
	vetorDestruicao.clear();

	while(!filaVisitar.empty())
	{
		filaVisitar.pop();
	}

	mapaVisitado[hex] = true;
	filaVisitar.push(hex);

	explodeRecursivo(grafoHexagon, 0);
}

 
void 
Bomba::explodeRecursivo(map<Hexagon*, vector<Hexagon*>> grafoHexagon, int num)
{
	if(num > (raioDestruicao) || filaVisitar.empty())
		return;

	//std::cout << "\n\n num: " << num << std::endl;

	Hexagon *hex = filaVisitar.front();
	filaVisitar.pop();

	if( (hex->haveTower() && !dynamic_cast<Base*>(hex->getObject()) ) )
	{
		if( ( (Torre *) hex->getObject() )->getNumLevel() <= numLevel)
		    vetorDestruicao.push_back(hex);
    }
    else if(hex->getSpy() != NULL)
	{
	    vetorDestruicao.push_back(hex);
	}
	std::vector<Hexagon *> adjacentes = grafoHexagon[hex];

	//std::cout << "adjacentes: " << adjacentes.size() << std::endl;
	
	for (unsigned int i = 0; i < adjacentes.size(); ++i)
	{
		//std::cout << "i: " << i << std::endl;
		if(mapaVisitado.find(adjacentes[i]) == mapaVisitado.end())
		{
			//std::cout << "i no if: " << i << std::endl;

			filaVisitar.push(adjacentes[i]);
			mapaVisitado[adjacentes[i]] = true;
		}
	}

	explodeRecursivo(grafoHexagon, num + 1);
}

std::vector<Hexagon *> 
Bomba::getVetorDestruicao()
{
	return vetorDestruicao;
}
