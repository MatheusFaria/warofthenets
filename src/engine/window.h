#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include "render.h"

class Window{
public:
	Window(int, int, int, int, const char *);
	~Window();

	void createWindow();
	
	Render getRender();

private:
	SDL_Window * window;
	int width;
	int height;
	int x;
	int y; 
	const char * title;
	Render render;
};

#endif
