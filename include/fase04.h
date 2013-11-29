#ifndef FASE04_H
#define FASE04_H

#include "condicaodevitoria.h"

class Fase04 : public CondicaoDeVitoria {

public:

	virtual bool verificarSeVenceu(void **args, int numArgs);
	virtual bool iniciarCondicoes(void **args, int numArgs);
};

#endif
