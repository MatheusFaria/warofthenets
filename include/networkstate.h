#ifndef NETWORK_STATE_H
#define NETWORK_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "networkmanager.h"
#include "textfield.h"
#include <vector>
#include <string>


class NetworkState : public GameState{

public:

	NetworkState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;

private:

	std::vector<MenuButton*> networkButtonObjects;
	static const std::string networkId;
	
	TextField * txtField;
	
};

#endif
