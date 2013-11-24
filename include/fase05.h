#ifndef FASE05_H
#define FASE05_H

#include "condicaodevitoria.h"

class Fase05 : public CondicaoDeVitoria {

public:

	virtual bool verificarSeVenceu(void **args, int numArgs);
	virtual bool iniciarCondicoes(void **args, int numArgs);
};

#endif
