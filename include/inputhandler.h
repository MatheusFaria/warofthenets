#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "vector2d.h"
#include "SDL2/SDL.h"
#include <vector>

enum mouse_buttons
{
		LEFT = 0,
		MIDDLE = 1,
		RIGHT = 2
};

class InputHandler
{
public:

	static InputHandler* Instance();

	void update();
	void clean();

	void onMouseButtonDown(SDL_Event&);
	void onMouseButtonUp(SDL_Event&);
	void onMouseMoviment(SDL_Event&);
	bool getMouseButtonState(int) const;

	Vector2D* getMousePosition();


private:

	InputHandler();
	~InputHandler();

	static InputHandler* input; 	

	std::vector<bool> mouseButtonStates;
	Vector2D* mousePosition;
};

#endif