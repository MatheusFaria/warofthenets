#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "image.h"
#include "text.h"
#include "bomba.h"
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

	GameObject* createObject(Hexagon *hex);
	void incObject();
	void showObject(Hexagon* hex);
	void deleteObject(Hexagon* hex);
	void decObject(GameObject* object);
	void destroyVectorObjects(std::vector<Hexagon*>);
	void iniciarTurno();
	void finalizarTurno();
	void calculateTime();

	void createHUD();
	void createMap();

	int windowWidth;
	int windowHeight;

	map<Hexagon*, vector<Hexagon*>> grafoHexagon;
	void foundAdjacents(Hexagon *hex);
	
	bool canConstruct(Hexagon *hex);

	static const std::string playId;

	std::vector<MenuButton*> hudButtons;

	std::vector<GameObject*> playObjects;

	std::vector<Bomba*> bombObjects;

	std::vector<Hexagon *> vectorHexagon;

	MenuButton *painelRecurso;
	MenuButton *recursoInformacao;
	MenuButton *recursoTower;
	MenuButton *recursoBomb;
	MenuButton *recursoSpy;
	MenuButton *fimTurno;
	MenuButton* painelCronometro;
	
	MenuButton *quit;

	std::string idSelected;
	
	int numTower;
	int numBomb;
	int numSpy;
	int numInformacao;
	int actualTime;
	int minutes, seconds;

    Text *txtNumInformation;
    Text *txtNumTower;
    Text *txtNumBomb;
    Text *txtNumSpy;    
    Text *txtTime;

	int eventX;
	int eventY;

};

#endif
