#ifndef CREDIT_STATE_H
#define CREDIT_STATE_H

#include "gameestate.h"
#include "keyboardevent.h"

class CreditState : public GameState, public KeyboardEvent{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;

	virtual bool eventInMe(SDL_Event sdlEvent);

private:

	static const std::string creditId;

	std::string imageId;
	std::string imagePath;
	int imageX;
	int imageY;

	float velocity;
};

#endif