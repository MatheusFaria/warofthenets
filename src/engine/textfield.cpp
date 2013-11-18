#include "textfield.h"
#include "log.h"
#include "render.h"

TextField::TextField(int x, int y, int wField, int hField, int fontSize)
:MouseClick()
{
	this->hField = hField;
	this->wField = wField;
	
	this->xField = x;
	this->yField = y;

	this->fontSize = fontSize;
	this->cursorBlink = 1;
	
	this->rect = NULL;
	this->cursor = NULL;
	this->text = NULL;
	this->shape = NULL;

	this->focused = false;
	this->wCursor = 5;
}

void
TextField::init()
{
	SDL_Color black = {0, 0, 0, 255};

	this->text = new Text("", this->fontSize);
	this->text->setFont("resources/font/monospaced.ttf");
	this->text->setColor(black);

	int letterh = this->text->getLetterHeight('M');
	this->wLetterSize = this->text->getLetterPrintWidth('M');

	if(this->hField < letterh)
		this->hField = letterh + 6;

	if(this->wField % this->wLetterSize)
		this->wField -= this->wField % this->wLetterSize;
	this->wField += this->wCursor;

	int texty = this->yField + (this->hField - letterh)/2;
	this->text->setPosition(this->xField, texty);

	this->rect = new Rectangle(this->wField, this->hField, Render::getInstance(), true);
	this->rect->setDrawColor(255, 255, 255, 255);
	this->rect->setPosition(this->xField, this->yField);

	this->shape = new Rectangle(this->wField, this->hField, Render::getInstance());
	this->shape->setDrawColor(0, 0, 0, 255);
	this->shape->setPosition(this->xField, this->yField);

	this->hCursor = this->hField - 6;
	this->xcursor = this->xField;
	this->ycursor = this->yField + (this->hField - this->hCursor)/2;

	this->cursor = new Rectangle(this->wCursor, this->hCursor, Render::getInstance(), true);
	this->cursor->setDrawColor(0, 0, 0, 255);
	this->cursor->setPosition(this->xcursor, this->ycursor);
}

TextField::~TextField() 
{
	if(this->rect != NULL)
		delete this->rect;
	if(this->shape != NULL)
		delete this->shape;
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

	if((x >= this->xField) && (x <= (this->xField + this->wField)) &&
		(y >= this->yField) && (y <= (this->yField + this->hField)))
	{
		//this->focused = true;
		//SDL_StartTextInput();
		return true;
	}

	//this->focused = false;
	//SDL_StopTextInput();
	return false;
}

bool
TextField::verifyEvent(SDL_Event sdlEvent)
{
    if((sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP))
        return true;
	else if(sdlEvent.type == SDL_TEXTINPUT && this->focused && this->xcursor < (this->xField + this->wField - this->wCursor))
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
	else if(sdlEvent.type == SDL_KEYUP && this->focused && this->xcursor < (this->xField + this->wField - this->wCursor))
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
	this->rect->draw();
	this->shape->draw();

	if(this->cursorBlink && this->focused)
	{
		this->cursor->draw();
	}

	this->text->draw();
}

void
TextField::setFocused(bool focused)
{
    this->focused = focused;
    
    if(focused)
	    SDL_StartTextInput();
    else
	    SDL_StopTextInput();
}

void
TextField::clean()
{
}

std::string 
TextField::getText() const
{
	return this->text->getValue();
}

int  
TextField::getWidth() const
{
	return this->wField;
}

int  
TextField::getHeight() const
{
	return this->hField;
}

void 
TextField::setPosition(int x, int y)
{
	this->xField = x;
	this->yField = y;
}

