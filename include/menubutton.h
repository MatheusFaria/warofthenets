#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "sdlgameobject.h"
#include "mouseclick.h"
#include "SDL2/SDL.h"

class MenuButton : public SDLGameObject, public MouseClick {

public:
	MenuButton(int, int, string, string);

	virtual void draw();
	virtual void update();
	virtual void clean();

    virtual bool eventInMe(SDL_Event sdlEvent);
    virtual bool verifyEvent(SDL_Event sdlEvent);

private:

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2

	};

	bool released;
	
	SDL_Event sdlEvent;

};

#endif
