#include "networkplayer.h"

#include <iostream>
using namespace std;

int NetworkPlayer::SERVER_TYPE = 0;
int NetworkPlayer::CLIENT_TYPE = 1;
int NetworkPlayer::UNDEFINED_TYPE = -1;

NetworkPlayer::NetworkPlayer(std::string name, std::string ip, int port)
{
	this->name = name;
	this->ip = ip;
	this->port = port;
	this->serverAddr = NULL;
	this->clientAddr = NULL;
	this->package = new Data;
	this->type = UNDEFINED_TYPE;
}

NetworkPlayer::~NetworkPlayer() {}

int
NetworkPlayer::createServer()
{
	cout << "Creating IP" << endl;
	this->serverAddr = new IPaddress;
	if(SDLNet_ResolveHost(this->serverAddr, NULL, this->port) == -1)
		return -1;
	cout << "IP Created" << endl << "Create Socket" << endl;

	cout << "Cliente conectado: " << SDLNet_Read32(&this->serverAddr->host) << " ";
	cout << SDLNet_Read16(&this->serverAddr->port) << endl;

	this->serverSocket = SDLNet_TCP_Open(this->serverAddr);
	cout << "Socket Created" << endl;

	cout << "SDL_ERROR: " << SDLNet_GetError() << endl;

	if(this->serverSocket == NULL)
		return -1;

	cout << "Servidor Iniciado!" << endl;
	cout << "Aguardando cliente ..." << endl;

	this->type = SERVER_TYPE;
	return 0;
}

int
NetworkPlayer::createClient(std::string ip, int port)
{
	this->clientAddr = new IPaddress;
	if(SDLNet_ResolveHost(this->clientAddr, ip.c_str(), port) == -1)
		return -1;
	
	this->serverSocket = SDLNet_TCP_Open(this->clientAddr);

	if(this->serverSocket == NULL)
		return -1;
	
	cout << "Cliente Iniciado!" << endl;

	this->type = CLIENT_TYPE;
	return 0;
}

void
NetworkPlayer::sendMessage(Data * package)
{
	if(serverSocket == NULL)
		cout << "Server Socket NULL" << endl;
	else
		cout << "Server Socket NOT null" << endl;
	
	cout<<package->type<<endl;	
	
	switch(this->type)
	{
		case 0:
			SDLNet_TCP_Send(clientSocket, package, sizeof(Data));
			break;
		case 1:
			SDLNet_TCP_Send(serverSocket, package, sizeof(Data));
			break;
	}
}

void
NetworkPlayer::finalizeGame()
{
	cout << "INICIO finalizeGame()" << endl;

	//SDLNet_TCP_Close(this->serverSocket);
	//SDLNet_TCP_Close(this->clientSocket);

	SDLNet_Quit();

	cout << "FIM finalizeGame()" << endl;
}

void 
NetworkPlayer::closeSocket()
{
	/*switch(this->type)
	{
		case 0:
			SDLNet_TCP_Close(clientSocket);
			break;
		case 1:
			SDLNet_TCP_Close(serverSocket);
			break;
	}*/

	clientSocket = NULL;
	serverSocket = NULL;		
}

int 
NetworkPlayer::receiveMessage()
{
	//if(clientSocket == NULL)
		//cout << "Client Socket NULL" << endl;
	//else
		//cout << "Client Socket NOT null" << endl;
	switch(this->type)
	{
		case 0:
			return SDLNet_TCP_Recv(clientSocket, this->package, sizeof(Data));
			
		case 1:
			return SDLNet_TCP_Recv(serverSocket, this->package, sizeof(Data));
			
	}
}

Data *
NetworkPlayer::getPackage()
{
	return this->package;
}

int
NetworkPlayer::acceptConnection()
{
	this->clientSocket = SDLNet_TCP_Accept(this->serverSocket);
	if(this->clientSocket)
	{
		this->clientAddr = SDLNet_TCP_GetPeerAddress(this->clientSocket);
		if(this->clientAddr)
		{
			cout << "Cliente conectado: " << SDLNet_Read32(&this->clientAddr->host) << " ";
			cout << SDLNet_Read16(&this->clientAddr->port) << endl;
			return 0;
		}
		else
		{
			cout << "Erro na CONEXAO: " << SDLNet_GetError() << endl;
			return -1;
		}																											            
	}

	return -1;
}

