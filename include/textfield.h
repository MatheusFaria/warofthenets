#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "mouseclick.h"
#include "rectangle.h"
#include "text.h"
#include "sdlgameobject.h"
#include <string>

class TextField: public MouseClick, SDLGameObject{
public:
	TextField(int x, int y, std::string shapePath, int hField, int wField, int fontSize = 30, int nFrames = 1);
	~TextField();

	void init();

	bool eventInMe(SDL_Event sdlEvent);
	bool verifyEvent(SDL_Event sdlEvent);
	void update();
	void draw();
	void clean();

private:
	int cursorIndex;
	int hField, wField;
	int xField, yField;
	int fontSize;
	int cursorBlink;
	bool focused;
	Rectangle * rect;
	Rectangle * cursor;
	Text * text;
};

#endif
