#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "gameobject.h"
#include "LoaderParams.h"

class SDLGameObject : public GameObject
{

public:

	SDLGameObject(LoaderParams* params);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:

	int	x;
	int y;
	int width;
	int height;
	string imageId;
	int currentRow;
	int currentFrame;

};

#endif