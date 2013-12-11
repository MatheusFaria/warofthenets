#include "fase02.h"
#include "hexagon.h"
#include "playstate.h"

#include <iostream>
using namespace std;

bool
Fase02::iniciarCondicoes(void **, int)
{
	return true;
}

bool 
Fase02::verificarSeVenceu(void **args, int)
{
	int* infoAtual = (int*) args[0];
	int* infoNecessaria = (int*) args[1];

	if(*infoAtual>=*infoNecessaria)
		return true;
	else
		return false;
}
