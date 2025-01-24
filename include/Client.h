#pragma once

#include "Socket.h"
#include <string>

class Client {
public:
    Client();
    ~Client();

    bool connectToServer(const std::string& ip, int port);
    bool sendMessage(const std::string& message);
    std::string receiveMessage();

    void disconnect();

private:
    Socket clientSocket;
};