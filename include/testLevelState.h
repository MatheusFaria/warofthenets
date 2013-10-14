#ifndef TEST_LEVEL_STATE_H
#define TEST_LEVEL_STATE_H

#include "gameestate.h"
#include "gameobject.h"
#include "image.h"
#include "text.h"
#include "render.h"
#include "mouse_click.h"
#include "keyboard_event.h"
#include "input_handler.h"
#include "hexagon.h"

#include <list>

using namespace std;

class KeyboardNum : public KeyboardEvent {

public:
    virtual bool eventInMe(SDL_Event sdlEvent)
    {
        if(sdlEvent.key.type == SDL_KEYDOWN)
        {
            if(sdlEvent.key.keysym.sym == SDLK_1)
                return true;
            if(sdlEvent.key.keysym.sym == SDLK_2)
                return true;
            if(sdlEvent.key.keysym.sym == SDLK_3)
                return true;
        }
        
        return false;
    }

};

class TestLevelState : public GameState, MouseClick, Event::EventListener{

public:
    
    TestLevelState(int windowWidth, int windowHeight, Render *rend);
    ~TestLevelState();
    
    virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;
	
	virtual bool eventInMe(SDL_Event sdlEvent);
	virtual void onEvent(Event *event, SDL_Event sdlEvent);

private:
    string adressImage;
    
    InputHandler *inputHandler;
    
    list<Image *> *listImage;
    
    KeyboardNum *keyboardNum;
    
    Hexagon *hex;
    SDL_Texture *hexTexture;
    
    int windowWidth;
    int windowHeight;
    
    int x;
    int y;
    
    Render *rend;
    
    static const std::string menuId;
};


#endif
