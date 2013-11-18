#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "mouseclick.h"
#include "rectangle.h"
#include "text.h"
#include <string>

class TextField: public MouseClick{
public:
	TextField(int x, int y, int wField, int hField, int fontSize = 30);
	~TextField();

	void init();

	bool eventInMe(SDL_Event sdlEvent);
	bool verifyEvent(SDL_Event sdlEvent);
	void onFocusChange();
	
	void update();
	void draw();
	void clean();

	std::string getText() const;
	int getWidth() const;
	int getHeight() const;

	void setPosition(int x, int y);

private:
	int hField, wField;
	int wLetterSize;
	int xField, yField;
	int xcursor, ycursor;
	int wCursor, hCursor;
	int fontSize;
	int cursorBlink;
	Rectangle * rect;
	Rectangle * shape;
	Rectangle * cursor;
	Text * text;
};

#endif
