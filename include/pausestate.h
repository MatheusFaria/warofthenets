#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include <vector>


class PauseState : public GameState{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId();

private:

	static void toMenu();
	static void backToGame();

	std::vector<GameObject*> pauseObjects;
	static const std::string pauseId;
};

#endif
