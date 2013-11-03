#ifndef HEXAGON_H
#define HEXAGON_H

#include "drawableobject.h"
#include "gameobject.h"
#include "mouseclick.h"

class Hexagon: virtual public DrawableObject, public MouseClick{
public:
	Hexagon(int, Render *);
	~Hexagon();

	virtual bool verifyEvent(SDL_Event sdlEvent);
	virtual bool eventInMe(SDL_Event sdlEvent);

	void update();
	bool setObject(GameObject* _object);
	void destroyGameObject();
	
	GameObject* getObject();

	bool isMouseRight();
	bool isMouseLeft();
	bool isMouseMiddle();

private:
	int size;

	void putObjectInSurface();

	GameObject *object;

	void setEventMouse(int mouse_state);
	void resetEventMouse();

	bool eventMouse[3];

	enum mouse_state
	{
		MOUSE_RIGHT = 0,
		MOUSE_LEFT = 1,
		MOUSE_MIDDLE = 2

	};

};

#endif
