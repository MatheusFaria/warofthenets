#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "gameobject.h"
#include "vector2d.h"
#include <string>

using namespace std;

class SDLGameObject : public GameObject
{

public:

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual int getX();
	virtual void setX(int x);

	virtual int getY();
	virtual void setY(int y);

	virtual int getWidth();
	virtual int getHeight();

    Vector2D getPosition();
	virtual void setPosition(int, int);
	

	int getCurrentRow();

	void incCurrentRow();
	void decCurrentRow();



protected:

	SDLGameObject(int, int, int, int, string, string, int = 1);

	Vector2D position;
	int width;
	int height;
	string imageId;
	string imagePath;
	int currentRow;
	int currentFrame;
	int numFrames;

};

#endif
