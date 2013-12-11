#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "menubutton.h"
#include "keyboardevent.h"
#include "image.h"
#include "mouseclick.h"
#include <vector>

class GameOverState : public GameState , public KeyboardEvent,
                      public MouseClick::MouseClickListener {

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
	
	virtual void enable();
	virtual void disable();

	virtual std::string getStateId() const;

	virtual bool eventInMe(SDL_Event sdlEvent);
	
	virtual void onMouseClick(MouseClick *mouseClick);

private:

	std::vector<GameObject*> gameOverObjects;
	static const std::string gameOverId;	
    
    Image *background;
    Image *imgLogo;
    MenuButton *newGame;
    MenuButton *quitToMenu;
    
    float velocity;
	float previousTime;
	
	SDL_Renderer *rend;
    SDL_Rect rectBackground;
    int alpha;
};

#endif
