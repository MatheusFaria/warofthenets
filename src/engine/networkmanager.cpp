#include "networkmanager.h"
#include "SDL2/SDL_net.h"

#include <iostream>
using namespace std;

int NetworkManager::PORT = 9000;
NetworkManager* NetworkManager::instance = NULL;

NetworkManager::NetworkManager()
{
	this->client = NULL;
	this->wasInit = false;
	this->listenThread = NULL;
}

NetworkManager::~NetworkManager() {}

NetworkManager*
NetworkManager::Instance()
{
	if(NetworkManager::instance == NULL)
		instance = new NetworkManager();

	return instance;
}

int
NetworkManager::init()
{
	if(SDLNet_Init() == -1)
		return -1;
	
	this->wasInit = true;
	atexit(SDLNet_Quit);
	return 0;
}

int NetworkManager::launchCommunication()
{
	this->listenThread = SDL_CreateThread(listenNetwork, "listenNetwork", this);
	if(this->listenThread == NULL)
		return -1;
	return 0;
}

void  NetworkManager::finishCommunication()
{
	int returnCode;
	if(this->listenThread != NULL)
		SDL_WaitThread(this->listenThread, &returnCode);
}

void
NetworkManager::createRoom(std::string name, std::string ip)
{
	cout << "Create Server" << endl;
	this->client = new NetworkPlayer(name, ip, PORT);
	cout << "Object Server Created" << endl;
	cout << this->client->createServer() << endl;
	cout << "Server Created" << endl;
	while(this->client->acceptConnection());
}

int
NetworkManager::joinRoom(std::string name, std::string ip)
{
	this->client = new NetworkPlayer(name, ip, PORT);
	this->client->createClient(ip, PORT);
	return 0;
}


Data
NetworkManager::receiveMessage()
{
	Data msg;
	
	if(messages.empty())
	{
		msg.type = -1;
		return msg;
	}

	msg = messages.front();

	messages.pop();
	return msg;
}

void 
NetworkManager::sendMessage(Data message)
{
	cout << "Send Message" << endl;
	if(this->client == NULL)
	{
		cout << "Client NULL" << endl;
		return;
	}
	this->client->sendMessage(&message);
}

int
NetworkManager::listenNetwork(void * ptr)
{
	NetworkManager * net = (NetworkManager *) ptr;
	cout << "Recieve Message" << endl;
	if(net->client == NULL)
		cout << "Server NULL" << endl;
	
	Data * pkg = new Data;
	pkg->type = 0;
	while(pkg->type != -1)
	{
		net->client->receiveMessage();
		pkg = net->client->getPackage();
		if(pkg != NULL)
		{
			cout<<"Mensagem ouvida: "<<pkg->type<<endl;
			net->messages.push(*pkg);
		}	

		if(pkg == NULL)
			cout << "Package NULL" << endl;
		else
		{
			cout << "Package NOT null" << endl;
			//cout << pkg->type << endl;
		}
	}
	return 0;
}

