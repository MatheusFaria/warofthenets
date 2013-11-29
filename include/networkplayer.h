#ifndef NETWORK_PLAYER_H
#define NETWORK_PLAYER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include <string>

typedef struct _data {
	int type;
	int x, y;
} Data;

class NetworkPlayer{
public:
	NetworkPlayer(std::string name, std::string ip, int port);
	~NetworkPlayer();

	int createServer();
	int createClient(std::string ip, int port);

	void closeSocket();

	void sendMessage(Data * package);
	int receiveMessage();

	Data * getPackage(); 
	int acceptConnection();
	void finalizeGame();

	TCPsocket getServerSocket(){return serverSocket;};
	TCPsocket getClientSocket(){return clientSocket;};


	int getType(){return type;};

	static int SERVER_TYPE;
	static int CLIENT_TYPE;
	static int UNDEFINED_TYPE;
private:
	std::string name;
	std::string ip;
	int port;

	int type;



	IPaddress * serverAddr;
	IPaddress * clientAddr;
	TCPsocket serverSocket;
	TCPsocket clientSocket;

	Data * package;
};

#endif
