#include "text.h"
#include "log.h"

using namespace std;

const int Text::NORMAL = TTF_STYLE_NORMAL;
const int Text::BOLD = TTF_STYLE_BOLD;
const int Text::ITALIC = TTF_STYLE_ITALIC;
const int Text::UNDERLINE = TTF_STYLE_UNDERLINE;
const int Text::STRIKETHROUGH =  TTF_STYLE_STRIKETHROUGH;

const int Text::SOLID = 0;
const int Text::BLENDED = 1; 
const int Text::SHADED = 2;

const SDL_Color Text::whiteTransparent = {255, 255, 255, 255};

Text::Text(std::string value, int size, std::string fontpath, SDL_Color bgcolor, SDL_Color fgcolor, Render * render, int style)
:RenderableObject(render)
{
	this->value = value;
	this->size = size;
	this->fontPath = fontpath;
	this->backgroundColor = bgcolor;
	this->foregroundColor = fgcolor;
	this->style = style;
	this->font = NULL;
	this->mode = SHADED;

	if(!TTF_WasInit())
	{
		TTF_Init();
		atexit(TTF_Quit);
	}
}

Text::Text(std::string value, int size, std::string fontpath, SDL_Color fgcolor, Render * render, int mode, int style)
:RenderableObject(render)
{
	this->value = value;
	this->size = size;
	this->fontPath = fontpath;
	this->backgroundColor = whiteTransparent;
	this->foregroundColor = fgcolor;
	this->style = style;
	this->font = NULL;
	this->mode = mode;

	if(!TTF_WasInit())
	{
		TTF_Init();
		atexit(TTF_Quit);
	}
}

Text::~Text()
{
	if(this->font != NULL)
		TTF_CloseFont(this->font);
}

void 
Text::openFont()
{
	if(this->font != NULL)
		TTF_CloseFont(this->font);

	this->font = TTF_OpenFont(this->fontPath.c_str(), this->size);
	if(this->font == NULL)
	{
		Log::warn("Could not open the font " + fontPath);
	}
}

SDL_Texture * 
Text::generateTexture()
{
	this->updateText();

	SDL_Texture * textTexture = NULL;
	SDL_Surface * textSurface = this->generateSurfaceText();

	if(textSurface == NULL)
	{
		Log::warn("Could not genarate surface to the text font");
		return NULL;
	}
	
	textTexture = SDL_CreateTextureFromSurface(getRenderer(), textSurface);
	
	SDL_FreeSurface(textSurface);
	
	if(textTexture == NULL)
	{
		Log::warn("Could not genarate the texture to the text font");
	}

	return textTexture;
}

SDL_Surface *
Text::generateSurfaceText()
{
	switch(this->mode)
	{
		case SHADED:
			return TTF_RenderUTF8_Shaded(this->font, this->value.c_str(), 
												this->foregroundColor, 
												this->backgroundColor);
		case BLENDED:
			return TTF_RenderUTF8_Blended(this->font, this->value.c_str(), 
												this->foregroundColor);
		default:
			return TTF_RenderUTF8_Solid(this->font, this->value.c_str(), 
												this->foregroundColor);
	}
}

void
Text::updateText()
{
	this->openFont();
	if(this->font != NULL)
		TTF_SetFontStyle(this->font, this->style);
}

void 
Text::setFont(std::string fontPath)
{
	this->fontPath = fontPath;
}

void 
Text::setStyle(int style)
{
	this->style = style;
}

void
Text::setSize(int size)
{
	this->size = size;
}

void
Text::setBackgroundColor(SDL_Color bgcolor) 
{
	this->backgroundColor = bgcolor;
}

void
Text::setForegroundColor(SDL_Color fgcolor)
{
	this->foregroundColor = fgcolor;
}

void
Text::setValue(std::string value)
{
	this->value = value;
}

std::string
Text::getValue() const
{
	return this->value;
}
