#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "server.h"
#include "client.h"
#include "SDL2/SDL_net.h"

class Networkmanager {

public:
	Networkmanager(Server * server, Client * client);
	~Networkmanager();

private:
	Server * server;
	Client * client;

};

#endif

