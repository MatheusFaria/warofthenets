#include "sdlsettings.h"

bool 
SDLSettings::setUpEnviroment()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if(SDL_WasInit(SDL_INIT_EVERYTHING))
	{
		atexit(SDL_Quit);
		return true;
	}
	return false;
}

bool 
SDLSettings::setUpVideo()
{
	SDL_Init(SDL_INIT_VIDEO);
	if(SDL_WasInit(SDL_INIT_VIDEO))
	{
		atexit(SDL_Quit);
		return true;
	}
	return false;
}

