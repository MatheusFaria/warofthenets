#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
	Server(std::string, std::string);
	~Server();

private:
	std::string ip;
	std::string port;
};

#endif

