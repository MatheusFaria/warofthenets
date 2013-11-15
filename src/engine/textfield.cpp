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
}

void
TextField::init()
{
	this->rect = new Rectangle(this->wField, this->hField, Render::getInstance(), true);
	this->rect->setDrawColor(255, 255, 255, 255);
	this->rect->setPosition(this->xField, this->yField);


	int hcursor = this->hField - 6, wcursor = 5;
	this->xcursor = this->xField;
	this->ycursor = this->yField + (this->hField - hcursor)/2;

	this->cursor = new Rectangle(wcursor, hcursor, Render::getInstance(), true);
	this->cursor->setDrawColor(0, 0, 0, 255);
	this->cursor->setPosition(this->xcursor, this->ycursor);

	SDL_Color black = {0, 0, 0, 255};

	this->text = new Text("", this->fontSize);
	this->text->setFont("resources/font/monospaced.ttf");
	this->text->setColor(black);
	this->text->setPosition(this->xField, this->yField);

	this->wLetterSize = this->text->getLetterPrintWidth('M');
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
		SDL_StartTextInput();
		return true;
	}

	this->focused = false;
	SDL_StopTextInput();
	return false;
}

bool
TextField::verifyEvent(SDL_Event sdlEvent)
{
    if((sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP))
        return true;
	else if(((sdlEvent.type == SDL_TEXTINPUT)) && this->focused)
	{
		char typed = *sdlEvent.text.text;
		if(typed >= ' ' && typed <= '~')
		{
			this->text->setValue(this->text->getValue() + typed);
			this->xcursor += this->wLetterSize;
			this->cursor->setPosition(this->xcursor, this->ycursor);
		}
		return false;
	}
	else if(sdlEvent.type == SDL_KEYUP)
	{
		char typed = sdlEvent.key.keysym.sym;
		if(typed == SDLK_BACKSPACE)
		{
			string textValue = this->text->getValue();
			if(textValue.size() != 0)
				textValue = string(textValue.begin(), textValue.end() - 1);
			this->text->setValue(textValue);

			this->xcursor -= this->wLetterSize;
			if(this->xcursor < this->xField)
				this->xcursor = this->xField;

			this->cursor->setPosition(this->xcursor, this->ycursor);
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
	{
		this->cursor->draw();
	}

	this->text->draw();
}

void
TextField::clean()
{
}
