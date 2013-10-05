#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "gameestate.h"

class MenuState : public GameState{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const

private:

	static const std::string menuId;
};

#endif