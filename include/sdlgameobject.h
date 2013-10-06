#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "gameobject.h"
#include "LoaderParams.h"
#include "vector2d.h"

class SDLGameObject : public GameObject
{

public:

	

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:

	SDLGameObject(LoaderParams* params);

	Vector2D position;
	int width;
	int height;
	string imageId;
	int currentRow;
	int currentFrame;

};

#endif