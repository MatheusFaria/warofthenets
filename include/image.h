#ifndef IMAGE_H
#define IMAGE_H

#include "sdlgameobject.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Image : public SDLGameObject {

public:
	Image(std::string imagePath, int x = 0, int y = 0);
	

private:

};

#endif
