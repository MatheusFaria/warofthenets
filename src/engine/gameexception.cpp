#include "gameexception.h"
#include <string>

using namespace std;


GameException::GameException(string msg)
{
	this->message = msg;
}

string GameException::getMessage()
{
	return this->message;
}

