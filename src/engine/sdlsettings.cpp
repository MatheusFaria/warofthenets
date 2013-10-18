#include "sdlsettings.h"
#include "log.h"

bool 
SDLSettings::setUpEnviroment()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if(SDL_WasInit(SDL_INIT_EVERYTHING))
	{
		atexit(SDL_Quit);
		return true;
	}
	Log::error("Could not set up the enviroment.");
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
	Log::error("Could not set up the video.");
	return false;
}

