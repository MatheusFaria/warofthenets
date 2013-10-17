#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "sdlgameobject.h"

class MenuButton : public SDLGameObject{

public:
	MenuButton(int, int, int, int, string, void (*callback)());

	virtual void draw();
	virtual void update();
	virtual void clean();


private:

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2

	};

	void (*callback)();
	bool released;

};

#endif
