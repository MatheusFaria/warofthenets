#include "window.h"

#include <iostream>
using namespace std;

Window::Window(int width, int height, int x, int y, const char * title)
{
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->title = title;
}

Window::~Window()
{
	if(this->window != NULL)
		SDL_DestroyWindow(this->window);
	if(this->render != NULL)
		delete render;
}

void 
Window::createWindow()
{
	this->window = SDL_CreateWindow(this->title, this->x, this->y,
									this->width, this->height, SDL_WINDOW_SHOWN);
	if(!(this->window))
		cout << "The Window Could Not Be Created: [" << SDL_GetError() << "]" << endl;
		
	render = Render::getInstance();
	render->createRender(this->window);
}

Render * 
Window::getRender()
{
	return this->render;
}

