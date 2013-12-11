#ifndef HEXAGON_H
#define HEXAGON_H

#include "drawableobject.h"
#include "image.h"
#include "gameobject.h"
#include "mouseclick.h"
#include <vector>

class Hexagon: virtual public DrawableObject, public MouseClick{
public:
	Hexagon(int, Render *);
	~Hexagon();

	virtual bool verifyEvent(SDL_Event sdlEvent);
	virtual bool eventInMe(SDL_Event sdlEvent);

	void update();
	void draw();
	bool setObject(GameObject* _object);
	
	void activateSpy();
	
	void destroyTorre();
	void destroyBomba();
	void destroySpy();
	void destroyGameObject();
	
	GameObject* getObject();
	GameObject* getBomba();
	GameObject* getSpy();
	bool haveObject();

    bool haveTower();

	bool isMouseRight();
	bool isMouseLeft();
	bool isMouseMiddle();
	bool isVictoryPoint();

	bool isMyCoordinate(int x, int y);
	
	void addBackgroundImage(std::string imagePath);

private:
	int size;

	void putObjectInSurface();

    std::vector<Image*> backgroundImages;

	GameObject *object;
	GameObject *bomba;
	GameObject* spy;
	Image* vitoria;
	

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
