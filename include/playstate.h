#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "image.h"
#include "text.h"
#include "bomba.h"
#include "hexagon.h"
#include "spy.h"
#include "mouseclick.h"
#include "keyboardevent.h"
#include "hexagonmap.h"
#include "networkplayer.h"
#include <vector>
#include <map>
#include <queue>

class PlayState : public GameState, public KeyboardEvent,
				  public MouseClick::MouseClickListener{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;

	virtual void onMouseClick(MouseClick *mouseClick);
	virtual bool eventInMe(SDL_Event sdlEvent);


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
	void atualizarCronometro();
	void atualizarTorres();
	void atualizarMapa();
	void ativarBotoes(bool);

	void criarTorre(Hexagon *hex, Torre *tower);
	void criarTorreInimiga(Data data);
	void criarBomba(Hexagon *hex, Bomba *bomba);
	void criarEspiao(Hexagon *hex, Spy *spy);

	Hexagon * encontrarHexagono(int x, int y);

	void createHUD();
	void createMap();

	void receberMensagens();
	void parseData(Data);

	bool isMyTurn;

	int x;
	int y;

	int velocityX;
	int velocityY;

	int windowWidth;
	int windowHeight;

	int mapColumns;
	int mapRows;

	static const std::string playId;

    HexagonMap *hexagonMap;

	std::vector<MenuButton*> hudButtons;
	std::vector<Image*> hudImages;
	std::vector<GameObject*> playObjects;
	std::vector<Hexagon *> vectorHexagon;

	std::vector<Torre*> vectorEnemyTower;

	Image *hudBackground;


	MenuButton *levelInformacao;
	MenuButton *recursoInformacao;

	Image *levelTower;
	Image *levelBomb;
	Image *levelSpy;

	bool towerActualized;
	bool bombActualized;
	bool spyActualized;

	MenuButton *upgradeTower;
	MenuButton *upgradeBomb;
	MenuButton *upgradeSpy;

	MenuButton *recursoTower;	
	MenuButton *recursoBomb;	
	MenuButton *recursoSpy;

	MenuButton *fimTurno;
	MenuButton *painelCronometro;
	MenuButton *quit;

	Bomba* bombObject;
	std::string idSelected;
	
	int numTower;
	int numBomb;
	int numSpy;
	int numInformacao;
	int actualTime;
	int minutes, seconds;

	int numLevelTower;
	int numLevelBomb;
	int numLevelSpy; 

    Text *txtNumInformation;

    Text *txtNumTower;
    Text *txtNumBomb;
    Text *txtNumSpy;    

    Text *txtTime;

    Text *txtLevelTower;
    Text *txtLevelBomb;
    Text* txtLevelSpy;


	int eventX;
	int eventY;

};

#endif
