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
	this->lstThread = NULL;
}

NetworkManager::~NetworkManager() {}

NetworkManager*
NetworkManager::Instance()
{
	if(NetworkManager::instance == NULL)
		instance = new NetworkManager();

	return instance;
}

void 
NetworkManager::deleteInstance()
{
	if(instance != NULL)
	{
		delete instance;
		instance = NULL;
	}
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
	//this->listenThread = SDL_CreateThread(listenNetwork, "listenNetwork", this);
	//if(this->listenThread == NULL)
	this->lstThread = new thread(listenNetwork, this);
	if(this->lstThread == NULL)
		return -1;
	return 0;
}

void  NetworkManager::finishCommunication()
{
	cout << "\n\n INICIO finishCommunication" << endl;
	int returnCode;
	//if(this->listenThread != NULL)
	if(this->lstThread != NULL)
	{
		cout << "INICIO SDL_WaitThread" << endl;
		this->setFinished(true);

		if(this->client->getClientSocket() != NULL)
			SDLNet_TCP_Close(this->client->getClientSocket());

		if(this->client->getServerSocket() != NULL)
			SDLNet_TCP_Close(this->client->getServerSocket());

		client->closeSocket();

		cout<<"Passou por aqui"<<endl;
		
		this->lstThread->detach();	

		//SDL_WaitThread(this->listenThread, &returnCode);
		cout << "FIM SDL_WaitThread" << endl << endl;
	}
}

void
NetworkManager::createRoom(std::string name, std::string ip)
{
	cout << "Create Server" << endl;
	this->client = new NetworkPlayer(name, ip, PORT);
	cout << "Object Server Created" << endl;
	cout << this->client->createServer() << endl;
	cout << "Server Created" << endl;
	while(this->client->acceptConnection()){ SDL_Delay(1);}
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

	//cout << "Recieve Message" << endl;
	if(net->client == NULL)
		cout << "Server NULL" << endl;
	
	Data * pkg = new Data;
	pkg->type = -2;
	net->setFinished(false);
	while(pkg->type != -1 && !net->isFinished())
	{
		
		if(!net->isFinished())
			net->client->receiveMessage();
		
		pkg = net->client->getPackage();
	
		if(pkg != NULL)
		{
		   
			
			if(pkg->type == 0)
			    continue;
		
			net->messages.push(*pkg);
			
		}	

	
		if(pkg == NULL)
			cout << "Package NULL" << endl;
		else
		{
		
		}
		
	}

	cout << "\n\n Wait Thread" << endl << endl;

	//net->server->finalizeGame();
	//net->client->finalizeGame();

	return 0;
}

int
NetworkManager::getTipo() const
{
	return this->tipo;
}

void 
NetworkManager::setTipo(int tipo)
{
	this->tipo = tipo;
}


void 
NetworkManager::setNome(std::string nome)
{
	this->nome = nome;
}

std::string
NetworkManager::getNome() const
{
	return this->nome;
}

void 
NetworkManager::setIp(std::string ip)
{
	this->ip = ip;
}

std::string 
NetworkManager::getIp()
{
	return this->ip;
}
