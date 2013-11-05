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

    Vector2D getPosition();
	virtual void setPosition(int, int);
	
	int getWidth();
	int getHeight();
	
	int getX();
	void setX(int x);
	
	int getY();
	void setY(int y);

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
