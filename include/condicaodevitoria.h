#ifndef CONDICAODEVITORIA_H
#define CONDICAODEVITORIA_H

#include <string>

class CondicaoDeVitoria {
public:

	virtual bool verificarSeVenceu(void **args, int numArgs) = 0;
	virtual bool iniciarCondicoes(void **args, int numArgs) = 0;
};

#endif
