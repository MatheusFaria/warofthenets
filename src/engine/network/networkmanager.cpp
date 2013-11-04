#include "networkmanager.h"

Networkmanager::Networkmanager(Server * server, Client * client)
{
	this->server = server;
	this->client = client;
}

Networkmanager::~Networkmanager()
{

}
