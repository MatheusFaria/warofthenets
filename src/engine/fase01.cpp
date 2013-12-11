#include "fase01.h"
#include "hexagon.h"
#include "playstate.h"

#include <iostream>
using namespace std;

bool
Fase01::iniciarCondicoes(void **args, int)
{
	PlayState *estado = (PlayState *) args[0];
	estado->criarPontoVitoria();
	return true;
}

bool 
Fase01::verificarSeVenceu(void **args, int)
{
	cout << "\n verificarSeVenceu \n" << endl;

	PlayState *estado = (PlayState *) args[0];
	Hexagon *hex = (Hexagon *) args[1];
	return estado->verificarVitoria(hex);
}
