#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include "networkplayer.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL_thread.h"
#include <queue>

class NetworkManager{
public:
	NetworkManager();
	~NetworkManager();

	int launchCommunication();
	void finishCommunication();

	void createRoom(std::string name, std::string ip);
	int joinRoom(std::string name, std::string ip);
	Data receiveMessage();
	void sendMessage(Data message);

	void deleteRoom(std::string ip);

private:
	NetworkPlayer * server;
	NetworkPlayer * client;
	static int PORT;
	bool wasInit;
	std::queue<Data> messages;
	SDL_Thread * listenThread;

	int init();
	static int listenNetwork(void * ptr); 
	void runNetwork();
};

#endif
