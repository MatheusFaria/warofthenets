#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "SDL2/SDL.h"
#include <list>


class MouseEventListener
{

public:
    virtual ~MouseEventListener(){}
    
    virtual void onMouseEvent(const SDL_Event& event) = 0;
    
};

class MouseEvent {


public:
	MouseEvent & getInstance();
	
	void sendListener(const SDL_Event& event);
	
	void addListener(MouseEventListener *listener);
	void removeListener(MouseEventListener *listener);
	
private:
	list<MouseEventListener> *listeners;
	MouseEvent *instance;
}


#endif






