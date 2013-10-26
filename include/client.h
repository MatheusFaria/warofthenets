#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "server.h"

class Client {
public:
	Client(std::string, std::string, Server *);
	~Client();

private:
	std::string ip;
	std::strinf port;
	Server * server;
}

#endif

