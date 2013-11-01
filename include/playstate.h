#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "image.h"
#include "hexagon.h"
#include "mouseclick.h"
#include <vector>

class PlayState : public GameState, public MouseClick,
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

	void createHUD();
	void createMap();

	int windowWidth;
	int windowHeight;

	static const std::string playId;
	std::vector<GameObject*> playObjects;

	Hexagon *hex;

	MenuButton *painelRecurso;
	MenuButton *recursoTower;
	MenuButton *recursoBomb;
	MenuButton *recursoSpy;

	std::string idSelected;

	int eventX;
	int eventY;

};

#endif
