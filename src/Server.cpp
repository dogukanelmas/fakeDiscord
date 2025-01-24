#include "../include/Server.h"

Server::Server() {}

Server::~Server() {
	stop();
}

bool Server::start(const std::string& ip, int port)
{
    if (!listeningSocket.create(SOCK_STREAM)) {
        // TODO: Give user a visible eror telling listening socket creation is failed.
        return false;
    }

    if (!listeningSocket.bind(ip, port)) {
        // TODO: Give user a visible eror telling listening socket binding is failed. Give the user which port and ip is tried to be connected.
        return false;
    }

    if (!listeningSocket.listen()) {
        // TODO: Give user a visible eror telling listening on socket is failed.
        return false;
    }

    // TODO: Well the server is started and the user somehow needs to know it. Figure it out :b
    return true;
}

void Server::stop(){
    for (auto& client : clientSockets) {
        client.close();
    }
    clientSockets.clear();
    listeningSocket.close();
    // TODO: Tell the user server is stopped somehow.
}

void Server::handleConnections() {
    SOCKET newClientSocket = listeningSocket.accept();
    if (newClientSocket != INVALID_SOCKET) {
        Socket client;
        client.close(); 
        clientSockets.push_back(client);
        // TODO: Tell the host a new client is connected.
    }
}

void Server::broadcast(const std::string& message) {
    for (auto& client : clientSockets) {
        if (client.send(message) == SOCKET_ERROR) {
            // TODO: If sending the mesage is failed, tell the host which client did not receive the message visibly.
        }
    }
}
