#include "text.h"
#include "log.h"

Text::Text(string value, int size, int style)
:SDLGameObject(0, 0, 0, 0, value)
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
	setWidth(textSurface->clip_rect.w);
	setHeight(textSurface->clip_rect.h);
	
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

string
Text::getValue()
{
	return this->value;
}
