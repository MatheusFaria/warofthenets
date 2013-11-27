#ifndef OPTIONSTATE_H
#define OPTIONSTATE_H

#include "gameestate.h"
#include "mouseclick.h"
#include "gameobject.h"
#include "menubutton.h"
#include "image.h"
#include "keyboardevent.h"
#include <vector>

class OptionState : public GameState, MouseClick::MouseClickListener,
                           KeyboardEvent{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;
	
	virtual void onMouseClick(MouseClick *mouseClick);
	
	virtual bool eventInMe(SDL_Event sdlEvent);

	void createMenu();

private:

	static const std::string optionId;
	
	std::vector<GameObject *> vectorGameObjects;
	
	MenuButton *enableAudio;
	MenuButton *disableAudio;
	
	Image *option;
	
	SDL_Renderer *rend;
    SDL_Rect rectBackground;
	
	bool soundEnable;
};



#endif
