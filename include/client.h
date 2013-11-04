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
	std::string port;
	Server * server;
};

#endif

