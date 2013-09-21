#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include <string>

using namespace std;

class GameException{

public:
	GameException(string msg);
	string getMessage();

private:
	string message;
};

#endif
