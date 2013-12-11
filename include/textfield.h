#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "mouseclick.h"
#include "rectangle.h"
#include "text.h"
#include <string>

class TextField: public MouseClick{
public:
	TextField(int x, int y, int wField, int hField, int fontSize = 30);
	virtual ~TextField();

	void init();

	bool eventInMe(SDL_Event sdlEvent);
	bool verifyEvent(SDL_Event sdlEvent);
	void update();
	void draw();
	void clean();

	std::string getText() const;
	int getWidth() const;
	int getHeight() const;
	
	int getX() const;
	int getY() const;

	void setPosition(int x, int y);
	void setText(std::string msg);
	
	void setFocused(bool focused);

private:
	int hField, wField;
	int wLetterSize;
	int xField, yField;
	int xcursor, ycursor;
	int wCursor, hCursor;
	int fontSize;
	int cursorBlink;
	bool focused;
	Rectangle * rect;
	Rectangle * shape;
	Rectangle * cursor;
	Text * text;
};

#endif
