#include "warn.h"
#include "inputhandler.h"
#include "game.h"

Warn::Warn(std::string warnMessage, std::string okButtonPath, std::string okButtonMusicPath, std::string fontPath, int fontSize)
{
	this->message = warnMessage;
	this->buttonPath = okButtonPath;
	this->musicPath = okButtonMusicPath;
	this->fontPath = fontPath;
	this->fontSize = fontSize;

	this->bgColor = {0, 0, 0, 200};
	this->letterColor = {255, 255, 255, 255};
	this->text = NULL;
	this->okButton = NULL;
	this->bg = NULL;
	this->show = true;
	this->clicked = false;
}

Warn::~Warn()
{
	if(this->text != NULL)
		delete this->text;
	if(this->okButton != NULL)
		delete this->okButton;
	if(this->bg != NULL)
		delete this->bg;
}

void
Warn::init()
{
	this->bg = new Rectangle(Game::Instance()->getWindow()->getWidth(),
							Game::Instance()->getWindow()->getHeight(),
							Render::getInstance(), true);
	this->bg->setDrawColor(this->bgColor.r,this->bgColor.g,this->bgColor.b,this->bgColor.a);
	this->bg->setPosition(0, 0);

	this->text = new Text(this->message, this->fontSize);
	this->text->setFont(this->fontPath);
	this->text->setColor(this->letterColor);
	int x = Game::Instance()->getWindow()->getWidth()/2 - this->text->getWidth()/2;
	int y = Game::Instance()->getWindow()->getHeight()/2 - this->text->getHeight()/2;
	this->text->setPosition(x, y);

	x += this->text->getWidth();
	y += this->text->getHeight() + 30;

	this->okButton = new MenuButton(x, y, this->buttonPath, this->buttonPath, 3, true); 
	this->okButton->setEventListener(this);
	this->okButton->setAudioOnClick(this->musicPath, "playClick");
	InputHandler::getInstance()->addMouseClick(this->okButton);

}

void
Warn::setScreenBlackness(int alpha)
{
	this->bgColor.a = alpha;
	this->bg->setDrawColor(this->bgColor.r,this->bgColor.g,this->bgColor.b,this->bgColor.a);
}

void
Warn::setText(std::string text)
{
	this->text->setValue(text);
}

void
Warn::setScreenColor(SDL_Color screenColor)
{
	this->bgColor = screenColor;
	this->bg->setDrawColor(this->bgColor.r,this->bgColor.g,this->bgColor.b,this->bgColor.a);
}

void
Warn::setTextColor(SDL_Color textColor)
{
	this->letterColor = textColor;
	this->text->setColor(this->letterColor);
}

void
Warn::update()
{
	this->okButton->update();
}

void
Warn::draw()
{
	if(this->show)
	{
		this->bg->draw();
		this->text->draw();
		this->okButton->draw();
	}
}

void
Warn::clean() {}

void 
Warn::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == this->okButton)
	{
		this->show = false;
		this->clicked = true;
		InputHandler::getInstance()->removeMouseClick(this->okButton);
	}
}

bool 
Warn::getShow() const
{
	return this->show;
}

bool  
Warn::wasClicked() const
{
	return this->clicked;
}

void   
Warn::setClicked(bool click)
{
	this->clicked = click;
}

void
Warn::setShow(bool show)
{
	this->show = show;
	if(this->show == false)
		InputHandler::getInstance()->removeMouseClick(this->okButton);
	else
		InputHandler::getInstance()->addMouseClick(this->okButton);
}
