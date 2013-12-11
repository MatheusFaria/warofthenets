#ifndef HEXAGONMAP_H
#define HEXAGONMAP_H

#include "hexagon.h"
#include "event.h"
#include "gameobject.h"
#include "torre.h"
#include <vector>
#include <map>


class HexagonMap {

public:

    HexagonMap(int numColumns, int numRows);
    virtual ~HexagonMap();

	virtual void draw();
	virtual void update();
	virtual void clean();

    bool isVictory(Hexagon *hexagon);

    void setEventListener(Event::EventListener *eventListener);
    Hexagon* encontrarHexagono(int x, int y);
    Hexagon* getHexagon(int x, int y);
    void putObjectOnMap(int x, int y, GameObject* object);
    bool canConstruct(Hexagon *hexagon);
    
    bool actualizeSpy();    
    
    std::vector<Hexagon*> getVectorHexagon();
    std::map<Hexagon*, std::vector<Hexagon*>> getGrafoHexagon();
    
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);
    
    void updateMap();

    void setActive(bool active);

private:
    
	std::vector<Hexagon*> vectorHexagon;
	std::map<Hexagon*, std::vector<Hexagon*>> grafoHexagon;

    unsigned int numColumns;
    unsigned int numRows;
    
    int velocityX;
    int velocityY;

    
    void createMap();
    
    bool estaConectadoNaBase(Hexagon *hexagono);
    bool existeTorreNoHexagono(Hexagon *hexagon);
    
    void addHexagonsOnInputHandler();
    void removeHexagonsOnInputHandler();
    
    void foundAdjacents(Hexagon *hex);
    bool isAdjacent(Hexagon *hexagon, int adjacentX, int adjacentY);
    bool addAdjacent(Hexagon *hexagon, Hexagon *hexagonAdjacent,
                     int adjacentX, int adjacentY);
                     
    
    bool possuiTorreAdjacente(Hexagon *hexagon);
    bool existeTorreEmAlgumHexagono();
    bool possuiTorreNoAdjacenteDoAdjacente(Hexagon *hexagon);
    

    void deleteHexagons();
	
	
};

#endif
