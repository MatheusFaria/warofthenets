#ifndef WINDOW_H
#define WINDOW_H

#include "SDL2/SDL.h"
#include <string>
using namespace std;

class Window{
public:
	Window(int, int, int, int, string);
	~Window();

	void createWindow();

private:
	SDL_Window * window;
	int width;
	int height;
	int x;
	int y; 
	string title;
};

#endif
