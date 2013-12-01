#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "image.h"
#include "text.h"
#include "bomba.h"
#include "hexagon.h"
#include "base.h"
#include "spy.h"
#include "mouseclick.h"
#include "keyboardevent.h"
#include "hexagonmap.h"
#include "networkplayer.h"
#include "warn.h"
#include "parseArquivo.h"
#include "condicaodevitoria.h"
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

	virtual void enable();
	virtual void disable();

	virtual std::string getStateId() const;

	virtual void onMouseClick(MouseClick *mouseClick);
	virtual bool eventInMe(SDL_Event sdlEvent);

	void criarPontoVitoria();
	bool verificarVitoria(Hexagon *hexagon);

    PlayState(string numFase);

private:

	GameObject* createObject(Hexagon *hex);

	void loadMusics();
	void selectStageMusic();

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
	void atualizarTorresInimigas();

	void atualizarEspiao();
	void atualizarEspioesInimigos();

	void atualizarMapa();
	void ativarBotoes(bool);
	void zerarCronometro();

	void criarTorre(Hexagon *hex, Torre *tower);
	void criarTorreInimiga(Data data);
	void criarBomba(Hexagon *hex, Bomba *bomba);
	void criarBombaInimiga(Data data);
	void criarEspiao(Hexagon *hex, Spy *spy);
	void criarEspiaoInimiga(Data data);
	void criarBase();

	Hexagon * encontrarHexagono(int x, int y);

	void createHUD();
	void createMap();
	void showHistory();

	void receberMensagens();
	void parseData(Data);
	void definirCondicaoDeVitoria();

	void definirPontoPartida();

	void receberVitoria();
	void informarVitoria();
	void finalizarJogo();
	void oponentDisconected();

	void moveMap(int x, int y);
	void goToBase();
	
	std::string numFase;
	std::string musicaFase;

	ParseArquivo parseArquivo;
	CondicaoDeVitoria *condicaoVitoria;

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

	std::vector<GameObject*> vectorEnemyObjects;

	Image *hudBackground;
	Image *hudTurno;


	MenuButton *levelInformacao;
	MenuButton *recursoInformacao;

	Image *levelTower;
	Image *levelBomb;
	Image *levelSpy;
	Image* vitoria;
	Image* background;

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

	GameObject* base1;
	GameObject* base2;
	GameObject* myBase;
	
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
    Text *txtTurno;

    Text *txtLevelTower;
    Text *txtLevelBomb;
    Text* txtLevelSpy;

    Warn * warnDisconect;

    bool fimDeJogo;
	int eventX;
	int eventY;

	float velocity;
	float previousTime;

	SDL_Renderer *rend;
    SDL_Rect rectBackground;
    int alpha;

};

#endif
