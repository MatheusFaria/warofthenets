#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class InputHandler()
{
public:

	InputHandler* Instance();

	void update();
	void clean();

private:

	InputHandler(){}
	~InputHandler(){}

	static InputHandler* input; 	

}

#endif