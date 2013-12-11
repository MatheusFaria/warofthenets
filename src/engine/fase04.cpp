#include "fase04.h"
#include "hexagon.h"
#include "playstate.h"

#include <iostream>
using namespace std;

bool
Fase04::iniciarCondicoes(void **args, int)
{
	PlayState *estado = (PlayState *) args[0];
	estado->criarPontoVitoria();
	return true;
}

bool 
Fase04::verificarSeVenceu(void **args, int)
{
	cout << "\n verificarSeVenceu \n" << endl;

	PlayState *estado = (PlayState *) args[0];
	Hexagon *hex = (Hexagon *) args[1];
	int *numTorres = (int *) args[2];
	
	if(*numTorres > 10)
	    return false;
	
	return estado->verificarVitoria(hex);
}
