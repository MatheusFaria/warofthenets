#include "fase03.h"
#include "hexagon.h"
#include "playstate.h"

#include <iostream>
using namespace std;

bool
Fase03::iniciarCondicoes(void **args, int numArgs)
{
	this->numInformacao = 0;
	return true;
}

bool 
Fase03::verificarSeVenceu(void **args, int numArgs)
{

	cout<<"Verificando logica de vitoria"<<numInformacao<<endl;
	int *informacao = (int*) args[0];
	int *condicaoVitoria = (int*) args[1];
	this->numInformacao += *informacao;
	
	return numInformacao >= *condicaoVitoria;
}
