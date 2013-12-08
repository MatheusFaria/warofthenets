#ifndef WARN_H
#define WARN_H

#include "text.h"
#include "rectangle.h"
#include "menubutton.h"
#include "mouseclick.h"
#include <string>

class Warn: public MouseClick::MouseClickListener{
public:
	Warn(std::string warnMessage, std::string okButtonPath, std::string okButtonMusicPath, std::string fontPath, int fontSize = 40);
	~Warn();

	void init();
	void update();
	void draw();
	void clean();
	void onMouseClick(MouseClick *mouseClick);

	bool getShow() const;

	bool wasClicked() const;
	void setClicked(bool click);

	void setShow(bool show);

	void setScreenBlackness(int alpha);
	void setText(std::string text);
	void setScreenColor(SDL_Color screenColor);
	void setTextColor(SDL_Color textColor);

	void enableButton();
	void disableButton();
	void hideButton();
	void showButton();
	
private:
	std::string message;
	std::string buttonPath;
	std::string musicPath;
	std::string fontPath;
	int fontSize;
	bool show;
	bool buttonShow;
	bool clicked;
	SDL_Color bgColor;
	SDL_Color letterColor;
	Text * text;
	MenuButton * okButton;
	Rectangle * bg;
};

#endif
