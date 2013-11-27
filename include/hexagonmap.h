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

    void setEventListener(Event::EventListener *eventListener);
    
    bool canConstruct(Hexagon *hexagon);
    
    
    std::vector<Hexagon*> getVectorHexagon();
    std::map<Hexagon*, std::vector<Hexagon*>> getGrafoHexagon();
    
    void setVelocityX(int velocityX);
    void setVelocityY(int velocityY);

    void setActive(bool active);

private:
    
	std::vector<Hexagon*> vectorHexagon;
	std::map<Hexagon*, std::vector<Hexagon*>> grafoHexagon;

    unsigned int numColumns;
    unsigned int numRows;
    
    int velocityX;
    int velocityY;

    
    void createMap();
    
    
    void addHexagonsOnInputHandler();
    void removeHexagonsOnInputHandler();
    
    void foundAdjacents(Hexagon *hex);
    bool isAdjacent(Hexagon *hexagon, int adjacentX, int adjacentY);
    bool addAdjacent(Hexagon *hexagon, Hexagon *hexagonAdjacent,
                     int adjacentX, int adjacentY);
                     
    
    bool possuiTorreAdjacente(Hexagon *hexagon);
    bool existeTorreEmAlgumHexagono();
    bool possuiTorreNoAdjacenteDoAdjacente(Hexagon *hexagon);
    
    void updateMap();

    void deleteHexagons();
	
	
};

#endif
