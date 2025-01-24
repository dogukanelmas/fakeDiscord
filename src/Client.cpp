#include "../include/Client.h"

Client::Client() {}

Client::~Client() {
	disconnect();
}

bool Client::connectToServer(const std::string& ip, int port)
{
    if (!clientSocket.create(SOCK_STREAM)) {
        // TODO: Tell the user creating a client socket is failed.
        return false;
    }

    if (!clientSocket.connect(ip, port)) {
        // TODO: Tell the client connecting the server at the given ip is failed.
        return false;
    }

    // TODO: Tell the user the connection is made with the server at ip.
    return true;
}

bool Client::sendMessage(const std::string& message)
{
    if (clientSocket.send(message) == SOCKET_ERROR) {
        // TODO: Tell the client the message is failed to send.
        return false;
    }
    return true;
}

std::string Client::receiveMessage() {
    char buffer[512];
    int bytesReceived = clientSocket.receive(buffer, sizeof(buffer));
    if (bytesReceived > 0) {
        return std::string(buffer, bytesReceived);
    }
    else if (bytesReceived == 0) {
        // TODO: Tell the client the server closed te connection.
    }
    else {
        // TODO: Tell the client it has failed to receive message.
    }
    return "";
}

void Client::disconnect() {
    clientSocket.close();
    // TODO: Give an indicator to the client that it has disconnected from the server.
}
