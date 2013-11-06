#include "networkmanager.h"
#include "SDL2/SDL_net.h"

#include <iostream>
using namespace std;

int NetworkManager::PORT = 9000;

NetworkManager::NetworkManager()
{
	this->client = NULL;
	this->wasInit = false;
}

NetworkManager::~NetworkManager() {}

int
NetworkManager::init()
{
	if(SDLNet_Init() == -1)
		return -1;
	
	this->wasInit = true;
	atexit(SDLNet_Quit);
	return 0;
}

void
NetworkManager::createRoom(std::string name, std::string ip)
{
	cout << "Create Server" << endl;
	this->client = new NetworkPlayer(name, ip, PORT);
	cout << "Object Server Created" << endl;
	cout << this->client->createServer(PORT) << endl;
	cout << "Server Created" << endl;
	//lanca Thread
	int rc = 1;
	while(rc)
	{
		rc = this->client->acceptConnection();
	}
	//join Thread
}

int
NetworkManager::joinRoom(std::string name, std::string ip)
{
	this->client = new NetworkPlayer(name, ip, PORT);
	this->client->createClient(ip, PORT);
	//this->client->createServer(PORT);
	return 0;
}

void
NetworkManager::deleteRoom(std::string ip)
{
}

void
NetworkManager::receiveMessage()
{
	cout << "Revieve Message" << endl;
	if(this->client == NULL)
		cout << "Server NULL" << endl;
	this->client->receiveMessage();		
	Data * pkg = this->client->getPackage();
	if(pkg == NULL)
		cout << "Package NULL" << endl;
	else
	{
		cout << "Package NOT null" << endl;
		cout << pkg->type << endl;
	}
}

void 
NetworkManager::sendMessage(int n)
{
	cout << "Send Message" << endl;
	Data * pkg = new Data;
	pkg->type = n;
	pkg->x = pkg-> y = 1;
	if(this->client == NULL)
		cout << "Client NULL" << endl;
	this->client->sendMessage(pkg);
}
