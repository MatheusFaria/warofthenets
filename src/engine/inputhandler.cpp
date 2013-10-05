#include "inputhandler.h"

InputHandler* InputHandler::input = NULL;

InputHandler*
InputHandler::Instance()
{
	if(input == null)
		input = new InputHandler();

	return input;
}

