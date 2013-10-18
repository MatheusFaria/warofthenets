#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "sdlgameobject.h"

#include <string>
using namespace std;

#define TTF_SOLID 0
#define TTF_BLENDED 1
#define TTF_SHADED 2

class Text{
public:
	Text(string, int, int = TTF_STYLE_NORMAL);
	~Text();

	void setFont(string);
	void setStyle(int);
	SDL_Texture * generateTexture(SDL_Renderer *, SDL_Color, SDL_Color, int = TTF_SOLID);

	SDL_Texture * getTexture();
	
	int getWidth();
	int getHeight();

private:
	SDL_Texture * text;
	string value;
	int mode;
	int size;
	int style;
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;
	TTF_Font * font;
	string fontPath;
	
	int width;
	int height;

	SDL_Surface * generateSurfaceText(int);
};

#endif