#include "text.h"
#include "render.h"
#include "log.h"

Text::Text(string value, int size, int style)
{
	this->value = value;
	this->size = size;
	this->style = style;

	if(!TTF_WasInit())
	{
		TTF_Init();
		atexit(TTF_Quit);
	}

	this->font = NULL;
	this->text = NULL;
	
}

Text::~Text()
{
	if(this->font != NULL)
		TTF_CloseFont(this->font);
	if(this->text != NULL)
		SDL_DestroyTexture(this->text);
}

void 
Text::setFont(string fontPath)
{
	this->fontPath = fontPath;
	if(this->font != NULL)
		TTF_CloseFont(this->font);

	this->font = TTF_OpenFont(this->fontPath.c_str(), this->size);
	if(this->font == NULL)
	{
		Log::warn("Could not open the font " + fontPath);
		return;
	}
	
	this->setStyle(this->style);
}

void 
Text::setStyle(int style)
{
	this->style = style;
	if(this->font != NULL)
		TTF_SetFontStyle(this->font, this->style);
}

void 
Text::setColor(SDL_Color color)
{
    this->color = color;
    generateTexture(Render::getInstance()->getRenderer(), color, color);
}

void 
Text::setText(string value)
{
    this->value = value;
    generateTexture(Render::getInstance()->getRenderer(), color, color);
}

SDL_Texture * 
Text::generateTexture(SDL_Renderer * render, SDL_Color foregroundColor, SDL_Color backgroundColor, int mode)
{
	if(this->font == NULL)
	{
		Log::warn("Could not genarate texture, because the font still NULL");
		return NULL;
	}

	if(this->text != NULL)
		SDL_DestroyTexture(this->text);

	this->foregroundColor = foregroundColor;
	this->backgroundColor = backgroundColor;
	this->text = NULL;

	SDL_Surface * textSurface = this->generateSurfaceText(mode);
	if(textSurface == NULL)
	{
		Log::warn("Could not genarate surface to the text font");
		return NULL;
	}
	
	this->text = SDL_CreateTextureFromSurface(render, textSurface);
	this->width = textSurface->clip_rect.w;
	this->height = textSurface->clip_rect.h;
	
	SDL_FreeSurface(textSurface);
	
	if(this->text == NULL)
	{
		Log::warn("Could not genarate the texture to the text font");
	}

	return this->text;
}

SDL_Surface *
Text::generateSurfaceText(int mode)
{
	this->mode = mode;

	switch(this->mode)
	{
		case TTF_SHADED:
			return TTF_RenderUTF8_Shaded(this->font, this->value.c_str(), 
												this->foregroundColor, 
												this->backgroundColor);
		case TTF_BLENDED:
			return TTF_RenderUTF8_Blended(this->font, this->value.c_str(), this->foregroundColor);
		default:
			return TTF_RenderUTF8_Solid(this->font, this->value.c_str(), this->foregroundColor);
	}
}

SDL_Texture *
Text::getTexture()
{
	return this->text;	
}

void
Text::draw()
{
    Render::getInstance()->renderTexture(text, position.getX(), position.getY());
}

void
Text::setPosition(int x, int y)
{
	this->position = Vector2D(x, y);
}

Vector2D
Text::getPosition()
{
    return position;
}


int
Text::getX()
{
    return position.getX();
}

void
Text::setX(int x)
{
    this->position = Vector2D(x, position.getY());
}

int
Text::getY()
{
    return position.getY();
}

void
Text::setY(int y)
{
    this->position = Vector2D(position.getX(), y);
}

int 
Text::getWidth()
{
    return this->width;
}

int 
Text::getHeight()
{
    return this->height;
}

std::string 
Text::getValue()
{
	return this->value;
}

void
Text::setValue(string value)
{
	this->value = value;
    generateTexture(Render::getInstance()->getRenderer(), color, color);
}
