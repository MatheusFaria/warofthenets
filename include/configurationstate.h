#ifndef CONFIGURATION_STATE_H
#define CONFIGURATION_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "mouseclick.h"
#include <map>
#include <string>


class ConfigurationState : public GameState, MouseClick::MouseClickListener{

public:

	ConfigurationState();

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void enable();
	virtual void disable();

	virtual std::string getStateId() const;
	void onMouseClick(MouseClick *mouseClick);

private:

	std::map<std::string, MenuButton*> buttons;
	std::map<std::string, Text*> texts;
	static int soundVolume, effectsVolume;
	static const std::string configurationId;
	
};

#endif
