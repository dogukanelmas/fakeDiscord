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

    // Called in a thread loop
    void handleConnections();

    // For host to broadcast messages
    void broadcast(const std::string& message);

private:
    Socket listeningSocket;
    std::vector<Socket> clientSockets;
};
