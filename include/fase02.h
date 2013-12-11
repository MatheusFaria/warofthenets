#ifndef FASE02_H
#define FASE02_H

#include "condicaodevitoria.h"

class Fase02 : public CondicaoDeVitoria {

public:

	virtual bool verificarSeVenceu(void **args, int);
	virtual bool iniciarCondicoes(void **args, int);
};

#endif
