#include "hexagonmap.h"
#include "inputhandler.h"

#include <iostream>

HexagonMap::HexagonMap(int numColumns, int numRows)
{
    this->numColumns = numColumns;
    this->numRows = numRows;
    
    this->velocityX = 0;
    this->velocityY = 0;
    
    createMap();
}

HexagonMap::~HexagonMap()
{

}

void
HexagonMap::draw()
{
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)            
		vectorHexagon[i]->draw();
}

void
HexagonMap::update()
{
    updateMap();
    
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
		vectorHexagon[i]->update();
}

void
HexagonMap::clean()
{
    removeHexagonsOnInputHandler();
    deleteHexagons();
}

std::vector<Hexagon*>
HexagonMap::getVectorHexagon()
{
    return vectorHexagon;
}

std::map<Hexagon*, std::vector<Hexagon*>>
HexagonMap::getGrafoHexagon()
{
    return grafoHexagon;
}

void 
HexagonMap::setVelocityX(int velocityX)
{
    this->velocityX = velocityX;
}

void 
HexagonMap::setVelocityY(int velocityY)
{
    this->velocityY = velocityY;
}

void
HexagonMap::createMap()
{
	const float yOff = 0.87*50;
	const float xOff = 0.5*50;

	for(unsigned int i = 0; i < numRows; i++)
	{	
		for(unsigned int j = 2; j < numColumns+2; j++)
		{
			float yPos = i * yOff * 2;

			if(j % 2 != 0)
				yPos += yOff;

			const float xPos = j * xOff * 3;

			Hexagon *hexagon = new Hexagon(50, Render::getInstance());
			hexagon->setDrawColor(0, 0, 0 , 255);
			hexagon->setPosition(xPos, yPos);
			vectorHexagon.push_back(hexagon);
			InputHandler::getInstance()->addMouseClick(hexagon);
            foundAdjacents(hexagon);
		}
	}
	
	/*
	std::cout << "createMap()" << std::endl;
	std::cout << "vectorHexagon.size()" << vectorHexagon.size() << std::endl;
	
	for(unsigned int i = 0; i < vectorHexagon.size(); i++)
    {
        std::cout << "vectorHexagon[i]->getX(): " << vectorHexagon[i]->getX() << std::endl;
        std::cout << "vectorHexagon[i]->getY(): " << vectorHexagon[i]->getY() << std::endl;
	}
	*/
}


void
HexagonMap::setEventListener(Event::EventListener *eventListener)
{
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
    	vectorHexagon[i]->setEventListener(eventListener);
}

void
HexagonMap::addHexagonsOnInputHandler()
{
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	    InputHandler::getInstance()->addMouseClick(vectorHexagon[i]);
}

void
HexagonMap::removeHexagonsOnInputHandler()
{
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	    InputHandler::getInstance()->removeMouseClick(vectorHexagon[i]);
}

void
HexagonMap::foundAdjacents(Hexagon *hexagon)
{
	int width = 100;
	int height = 87;
	int centerX = hexagon->getX() + (width/2);
	int centerY = hexagon->getY() + (height/2);

	int adjacentX;
	int adjacentY;

	for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	{
	    //CIMA
		adjacentX = centerX;
		adjacentY = centerY - height;
		if(addAdjacent(hexagon, vectorHexagon[i], adjacentX, adjacentY))
		    continue;
		
		//CIMA + ESQUERDA
		adjacentX = centerX - (width/2);
		adjacentY = centerY - (height/2);
		if(addAdjacent(hexagon, vectorHexagon[i], adjacentX, adjacentY))
		    continue;
		
		//CIMA + DIREITA
		adjacentX = centerX + (width/2);
		adjacentY = centerY - (height/2);
		if(addAdjacent(hexagon, vectorHexagon[i], adjacentX, adjacentY))
		    continue;
		
		//BAIXO
		adjacentX = centerX;
		adjacentY = centerY + height;
		if(addAdjacent(hexagon, vectorHexagon[i], adjacentX, adjacentY))
		    continue;
		
		//BAIXO + ESQUERDA
		adjacentX = centerX - (width/2);
		adjacentY = centerY + (height/2);
		if(addAdjacent(hexagon, vectorHexagon[i], adjacentX, adjacentY))
		    continue;
		
		//BAIXO + DIREITA
		adjacentX = centerX + (width/2);
		adjacentY = centerY + (height/2);
		if(addAdjacent(hexagon, vectorHexagon[i], adjacentX, adjacentY))
		    continue;
	}
}

bool
HexagonMap::isAdjacent(Hexagon *hexagon, int adjacentX, int adjacentY)
{
    return hexagon->isMyCoordinate(adjacentX, adjacentY);
}

bool
HexagonMap::addAdjacent(Hexagon *hexagon, Hexagon *hexagonAdjacent,
                        int adjacentX, int adjacentY)
{
    if(isAdjacent(hexagonAdjacent, adjacentX, adjacentY))
    {
        grafoHexagon[hexagon].push_back(hexagonAdjacent);
	    grafoHexagon[hexagonAdjacent].push_back(hexagon);
	    
	    return true;
    }
    
    return false;
}


bool 
HexagonMap::canConstruct(Hexagon *hexagon)
{
    vector<Hexagon *> adjacents;
    adjacents = grafoHexagon[hexagon];

    vector<Hexagon *> adjacentsAdj;
    
    if(!existeTorreEmAlgumHexagono())
        return true;
    
    if(possuiTorreAdjacente(hexagon))
        return false;
        
    if(possuiTorreNoAdjacenteDoAdjacente(hexagon))
        return true;

    

    
    return false;
}

bool
HexagonMap::existeTorreEmAlgumHexagono()
{
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
    {
    	if(vectorHexagon[i]->haveObject())
    		return true;
    }
    
    return false;
}

bool
HexagonMap::possuiTorreAdjacente(Hexagon *hexagon)
{
    vector<Hexagon *> adjacents;
    adjacents = grafoHexagon[hexagon];
    
    for(unsigned int i = 0; i < adjacents.size(); i++)
    {
    	if(adjacents[i]->haveObject())
    		return true;
    }
    
    return false;
}

bool
HexagonMap::possuiTorreNoAdjacenteDoAdjacente(Hexagon *hexagon)
{
    vector<Hexagon *> adjacents;
    vector<Hexagon *> adjacentsAdj;
    
    adjacents = grafoHexagon[hexagon];

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
HexagonMap::updateMap()
{
    int hexagonX;
    int hexagonY;
    
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	{
		hexagonX = vectorHexagon[i]->getX() - this->velocityX;
		hexagonY = vectorHexagon[i]->getY() - this->velocityY;
		
		vectorHexagon[i]->setX(hexagonX);
		vectorHexagon[i]->setY(hexagonY);
	}
}

void 
HexagonMap::deleteHexagons()
{
    for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	    delete vectorHexagon[i];
}

void 
HexagonMap::setActive(bool active)
{
	for(unsigned int i = 0; i < vectorHexagon.size(); i++)
	{
		vectorHexagon[i]->setActive(active);
	}
}

















