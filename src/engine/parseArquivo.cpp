#include "parseArquivo.cpp"
#include <fstream>

bool
ParseArquivo::loadArquivo(std::string path)
{
	char buffer[4096];
	std::string param;

	ifstream arquivo(path.c_str());

	while(arquivo.getline(buffer, 4096)){
		param = buffer;
		dados["objetivos"] = param;
	}

	std::cout << dados["objetivos"] << std::endl;

}