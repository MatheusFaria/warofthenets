#ifndef FASE03_H
#define FASE03_H

#include "condicaodevitoria.h"

class Fase03 : public CondicaoDeVitoria {

public:

	virtual bool verificarSeVenceu(void **args, int numArgs);
	virtual bool iniciarCondicoes(void **args, int numArgs);

	int getNumInformacao();

private:

	int numInformacao;	
};

#endif
