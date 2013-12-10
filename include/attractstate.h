#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "keyboardevent.h"
#include "image.h"
#include "event.h"
#include <vector>

class AttractState : public GameState, public Event {

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void enable();
	virtual void disable();

	virtual std::string getStateId() const;

	virtual bool eventInMe(SDL_Event sdlEvent);
	virtual bool verifyEvent(SDL_Event sdlEvent);

private:

	static const std::string attractId;
	
	SDL_Event sdlEvent;
    Image *imageAttract;
};

#endif
