#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"
#include "renderableobject.h"
#include <string>

class Text: public RenderableObject{
public:
	Text(std::string, int, std::string, SDL_Color, Render *, int = SOLID, int = TTF_STYLE_NORMAL);
	Text(std::string, int, std::string, SDL_Color, SDL_Color, Render *, int = TTF_STYLE_NORMAL);
	~Text();

	void setStyle(int);
	void setSize(int);
	void setBackgroundColor(SDL_Color);
	void setForegroundColor(SDL_Color);
	void setValue(std::string);
	void setFont(std::string);
	
	std::string getValue() const;

	static const int NORMAL;
	static const int BOLD;
	static const int ITALIC;
	static const int UNDERLINE;
	static const int STRIKETHROUGH;

private:
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;
	TTF_Font * font;

	std::string value;
	std::string fontPath;

	int mode;
	int size;
	int style;

	SDL_Surface * generateSurfaceText();
	SDL_Texture * generateTexture();
	void openFont();
	void updateText();

	static const int SOLID;
	static const int BLENDED;
	static const int SHADED;
	static const SDL_Color whiteTransparent;
};

#endif
