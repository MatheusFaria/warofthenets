#ifndef NETWORK_STATE_H
#define NETWORK_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "networkmanager.h"
#include "textfield.h"
#include "mouseclick.h"
#include "warn.h"
#include <map>
#include <string>


class NetworkState : public GameState, MouseClick::MouseClickListener{

public:

	NetworkState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	void enableAllClicks();
	void disableAllClicks();

	virtual std::string getStateId() const;
	void onMouseClick(MouseClick *mouseClick);

private:

	std::map<std::string, MenuButton*> buttons;
	std::map<std::string, Text*> texts;
	std::map<std::string, TextField*> textfields;
	Warn * warn;
	static const std::string networkId;
	
};

#endif
