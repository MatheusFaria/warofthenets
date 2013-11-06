#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "networkplayer.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"

class NetworkManager{
public:
	NetworkManager();
	~NetworkManager();

	void createRoom(std::string name, std::string ip);
	int joinRoom(std::string name, std::string ip);
	void receiveMessage();
	void sendMessage(int n);

	void deleteRoom(std::string ip);

private:
	NetworkPlayer * server;
	NetworkPlayer * client;
	static int PORT;
	bool wasInit;

	int init();
};

#endif
