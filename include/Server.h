#pragma once

#include "Socket.h"
#include <vector>
#include <string>

class Server {
public:
	Server();
	~Server();

	bool start(const std::string& ip, int port);
	void stop();
	void handleConnections();
	void broadcast(const std::string& message);

private:
	Socket listeningSocket;
	std::vector<Socket> clientSockets;
};