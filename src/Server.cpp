#include "../include/Server.h"
#include <Windows.h>

Server::Server() {}
Server::~Server() {
    stop();
}

bool Server::start(const std::string& ip, int port) {
    if (!listeningSocket.create(SOCK_STREAM)) {
        return false;
    }
    if (!listeningSocket.bind(ip, port)) {
        return false;
    }
    if (!listeningSocket.listen()) {
        return false;
    }
    MessageBoxA(nullptr, "Server started listening!", "Info", MB_OK);
    return true;
}

void Server::stop() {
    for (auto& client : clientSockets) {
        client.close();
    }
    clientSockets.clear();
    listeningSocket.close();
}

void Server::handleConnections() {
    SOCKET newClientSocket = listeningSocket.accept();
    if (newClientSocket != INVALID_SOCKET) {
        Socket client;
        client.setSocket(newClientSocket);
        clientSockets.push_back(client);

        MessageBoxA(nullptr, "A new client connected!", "Info", MB_OK);
    }
}

void Server::broadcast(const std::string& message) {
    for (auto& client : clientSockets) {
        if (client.send(message) == SOCKET_ERROR) {
            // Optionally remove or handle the client
            // MessageBoxA(nullptr, "Failed to broadcast to a client!", "Error", MB_OK);
        }
    }
}
