#ifndef TUTORIAL_STATE_H
#define TUTORIAL_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "mouseclick.h"
#include "image.h"
#include <map>
#include <string>

class TutorialState : public GameState, MouseClick::MouseClickListener{

public:

	TutorialState();

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
	std::map<int, Image*> images;
	static const std::string tutorialId;
	int page;
	int maxPage;
	int minPage;
};

#endif
