#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include <vector>

class MenuState : public GameState{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;

	void createMenu();

private:

	static void menuToPlay();
	static void exitFromMenu();

	static const std::string menuId;
	std::vector<GameObject*> menuObjects;

};

#endif