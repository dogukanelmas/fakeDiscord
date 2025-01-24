#pragma once

#include "Server.h"
#include "Client.h"
#include <string>

class Network {
public:
    Network();
    ~Network();

    bool initialize();
    void cleanup();

    // Server functions
    bool startServer(const std::string& ip, int port);
    void stopServer();

    // Client functions
    bool connectToServer(const std::string& ip, int port);
    void disconnectFromServer();

    // Unified event handling
    void checkNetworkEvents();

    // State
    bool isHosting() const;
    bool isConnected() const;

private:
    Server server;
    Client client;

    bool hosting;
    bool connected;
};