#include "textfield.h"
#include "log.h"
#include "render.h"

TextField::TextField(int x, int y, std::string shapePath, int hField, int wField, int fontSize, int nFrames)
:MouseClick(), SDLGameObject(x, y, 0, 0, shapePath, shapePath, nFrames)
{
	this->hField = hField;
	this->wField = wField;
	
	this->xField = getX() + (getWidth() - this->wField)/2;
	this->yField = getY() + (getHeight() - this->hField)/2;

	this->fontSize = fontSize;
	this->cursorBlink = 1;
	
	this->rect = NULL;
	this->cursor = NULL;
	this->text = NULL;

	this->focused = false;
	this->cursorIndex = 0;
}

void
TextField::init()
{
	this->rect = new Rectangle(this->wField, this->hField, Render::getInstance(), true);
	this->rect->setDrawColor(255, 255, 255, 255);
	this->rect->setPosition(this->xField, this->yField);


	int hcursor = this->hField - 6, wcursor = 5;
	int xcursor = this->xField + 1, ycursor = this->yField + (this->hField - hcursor)/2;

	this->cursor = new Rectangle(wcursor, hcursor, Render::getInstance(), true);
	this->cursor->setDrawColor(0, 0, 0, 255);
	this->cursor->setPosition(xcursor, ycursor);

	SDL_Color black = {0, 0, 0, 255};

	this->text = new Text(" ", this->fontSize);
	this->text->setFont("resources/font/monospaced.ttf");
	this->text->setColor(black);
	this->text->setPosition(this->xField, this->yField);
}

TextField::~TextField() 
{
	if(this->rect != NULL)
		delete this->rect;
	if(this->cursor != NULL)
		delete this->cursor;
	if(this->text != NULL)
		delete this->text;
}

bool 
TextField::eventInMe(SDL_Event sdlEvent)
{
	int x = sdlEvent.button.x;
	int y = sdlEvent.button.y;

	if(x >= this->xField && x <= (this->xField + this->wField) &&
		y >= this->yField && y <= (this->yField + this->hField))
	{
		this->focused = true;
		return true;
	}

	this->focused = false;
	return false;
}

bool
TextField::verifyEvent(SDL_Event sdlEvent)
{
    if((sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP))
        return true;
	else if(((sdlEvent.type == SDL_KEYDOWN) ||
        (sdlEvent.type == SDL_KEYUP)) && this->focused)
	{
		char typed = sdlEvent.key.keysym.sym;
		if(typed >= 'a' && typed <= 'z')
		{
			this->text->setValue(this->text->getValue() + typed);
			cout << typed << endl;
		}
        return false;
	}
    else
        return false;
}

void
TextField::update()
{
	int intervalo = 500;
	this->cursorBlink = (SDL_GetTicks()/intervalo) % 2;
}

void 
TextField::draw()
{
	SDLGameObject::draw();
	this->rect->draw();

	if(this->cursorBlink && this->focused)
		this->cursor->draw();

	this->text->draw();
}

void
TextField::clean()
{
}
