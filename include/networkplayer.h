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

	void sendMessage(Data * package);
	void receiveMessage();

	Data * getPackage(); 
	int acceptConnection();

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
