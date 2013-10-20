#ifndef MOUSECLICK
#define MOUSECLICK

#include "mouseevent.h"

class MouseClick : public MouseEvent {

public:

    class MouseClickListener : public MouseEvent::MouseEventListener {
	public:
		virtual ~MouseClickListener(){};
		virtual void onMouseEvent(MouseEvent *mouseEvent)
		{
		    MouseClick *mouseClick = (MouseClick *) mouseEvent;
		    onMouseClick(mouseClick);
		}
		virtual void onMouseClick(MouseClick *mouseClick) = 0;
	};
	

    MouseClick();
	~MouseClick();
	
	virtual bool eventInMe(SDL_Event sdlEvent) = 0;
	
	virtual bool verifyEvent(SDL_Event sdlEvent);
	
	static bool isMyEvent(SDL_Event sdlEvent);
};




#endif










































