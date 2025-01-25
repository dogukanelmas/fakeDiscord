#include "../include/Client.h"
#include <Windows.h>

Client::Client() {}
Client::~Client() {
    disconnect();
}

bool Client::connectToServer(const std::string& ip, int port) {
    if (!clientSocket.create(SOCK_STREAM)) {
        return false;
    }
    if (!clientSocket.connect(ip, port)) {
        return false;
    }
    MessageBoxA(nullptr, "Client connected to server!", "Info", MB_OK);
    return true;
}

bool Client::sendMessage(const std::string& message) {
    if (clientSocket.send(message) == SOCKET_ERROR) {
        MessageBoxA(nullptr, "Failed to send message!", "Error", MB_OK);
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
        // Connection closed
        // MessageBoxA(nullptr, "Server closed connection.", "Info", MB_OK);
    }
    else {
        // Error
        // MessageBoxA(nullptr, "Receive error!", "Error", MB_OK);
    }
    return "";
}

void Client::disconnect() {
    clientSocket.close();
    // MessageBoxA(nullptr, "Client disconnected.", "Info", MB_OK);
}
