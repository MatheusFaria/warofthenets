#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "gameobject.h"
#include "vector2d.h"
#include <string>

using namespace std;

class SDLGameObject : public GameObject
{

public:
	void setWidth(int);
	void setHeight(int);
	void setPosition(int, int);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:

	SDLGameObject(int, int, int, int, string);

	Vector2D position;
	int width;
	int height;
	string imageId;
	int currentRow;
	int currentFrame;

};

#endif
