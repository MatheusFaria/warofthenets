#include "log.h"
#include "SDL2/SDL.h"

void Log::warn(string msg)
{
	cout << msg << ": [" << SDL_GetError() << "]" << endl;	
}

void Log::error(string msg)
{
	cout << msg << ": [" << SDL_GetError() << "]" << endl;	
}

void Log::info(string msg)
{
	cout << msg << ": [" << SDL_GetError() << "]" << endl;	
}
