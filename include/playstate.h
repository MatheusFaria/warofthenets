#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "image.h"
#include "text.h"
#include "hexagon.h"
#include "mouseclick.h"
#include <vector>
#include <map>

class PlayState : public GameState,
				  public MouseClick::MouseClickListener{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;

	virtual void onMouseClick(MouseClick *mouseClick);
	//virtual bool eventInMe(SDL_Event sdlEvent);

private:

	GameObject* createObject();
	void incObject();
	void showObject(Hexagon* hex);
	void deleteObject(Hexagon* hex);
	void decObject(GameObject* object);

	void createHUD();
	void createMap();

	int windowWidth;
	int windowHeight;

	map<Hexagon*, vector<Hexagon*>> grafoHexagon;
	void foundAdjacents(Hexagon *hex);
	
	bool canConstruct(Hexagon *hex);

	static const std::string playId;
	std::vector<GameObject*> playObjects;

	std::vector<Hexagon *> vectorHexagon;

	MenuButton *painelRecurso;
	MenuButton *recursoTower;
	MenuButton *recursoBomb;
	MenuButton *recursoSpy;
	
	MenuButton *quit;

	std::string idSelected;
	
	int numTower;
	int numBomb;
	int numSpy;

    Text *txtNumTower;
    Text *txtNumBomb;
    Text *txtNumSpy;    

	int eventX;
	int eventY;

};

#endif
