#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include <vector>

class GameOverState{

public:

	void update();
	void render();

	bool onEnter();
	bool onExit();

	std::string getGameOverId() const;

private:

	std::vector<GameObject*> gameOverObjects;
	static const std::string gameOverId;	

};

#endif
