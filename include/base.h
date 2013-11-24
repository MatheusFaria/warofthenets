#ifndef BASE_H
#define BASE_H

#include "torre.h"
#include <string>

class Base : public Torre{

public:

	Base(int tipoBase, int informacoesPorTurno, int x, int y, std::string path);
	virtual int getInformacao();

	virtual void update();
	virtual void draw();

private:

	int informacoesPorTurno;

};


#endif