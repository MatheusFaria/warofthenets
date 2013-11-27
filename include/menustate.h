#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "mouseclick.h"
#include "menubutton.h"
#include <vector>

class MenuState : public GameState, MouseClick::MouseClickListener{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;
	
	virtual void onMouseClick(MouseClick *mouseClick);

	void createMenu();

private:

	static void menuToPlay();
	static void menuToCredit();
	static void menuToOption();
	static void exitFromMenu();

	static const std::string menuId;
	std::vector<GameObject*> menuObjects;
	
	MenuButton *playButton;
	MenuButton *aboutButton;
	MenuButton *exitButton;
	MenuButton *audioButton;

};

#endif
