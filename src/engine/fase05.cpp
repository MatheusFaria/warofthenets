#include "fase05.h"
#include "hexagon.h"
#include "playstate.h"

#include <iostream>
using namespace std;

bool
Fase05::iniciarCondicoes(void **, int)
{
	return true;
}

bool 
Fase05::verificarSeVenceu(void **args, int)
{
	int *levelTorre = (int*) args[0];
	int *levelSpy = (int*) args[1];
	int *levelBomba = (int*) args[2];

	return *levelTorre == 3 && *levelBomba == 3 && *levelSpy == 3;
}
