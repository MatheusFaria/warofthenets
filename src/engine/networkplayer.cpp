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
	this->serverAddr = new IPaddress;
	if(SDLNet_ResolveHost(this->serverAddr, NULL, this->port) == -1)
		return -1;

	this->serverSocket = SDLNet_TCP_Open(this->serverAddr);

	if(this->serverSocket == NULL)
		return -1;

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
	

	this->type = CLIENT_TYPE;
	return 0;
}

void
NetworkPlayer::sendMessage(Data * package)
{
	
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
	SDLNet_Quit();

}

void 
NetworkPlayer::closeSocket()
{
	switch(this->type)
	{
		case 0:
			SDLNet_TCP_Close(serverSocket);
			break;
		case 1:
			//SDLNet_TCP_Close(clientSocket);
			SDLNet_TCP_Close(serverSocket);
			break;
	}
		
}

int 
NetworkPlayer::receiveMessage()
{
	switch(this->type)
	{
		case 0:
			return SDLNet_TCP_Recv(clientSocket, this->package, sizeof(Data));
			
		case 1:
			return SDLNet_TCP_Recv(serverSocket, this->package, sizeof(Data));
			
	}

	return 0;
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
			return 0;
		}
		else
		{
			return -1;
		}																											            
	}

	return -1;
}

