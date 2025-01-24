#include "../include/Network.h"

Network::Network() : hosting(false), connected(false) {}

Network::~Network() {
    cleanup();
}

bool Network::initialize() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // TODO: I dont know who to give this error to but figure it out and tell them WSAStartup failed.
        return false;
    }
    return true;
}

void Network::cleanup() {
    if (hosting) {
        stopServer();
    }
    if (connected) {
        disconnectFromServer();
    }
    WSACleanup();
}

bool Network::startServer(const std::string& ip, int port) {
    if (server.start(ip, port)) {
        hosting = true;
        return true;
    }
    return false;
}

void Network::stopServer() {
    if (hosting) {
        server.stop();
        hosting = false;
    }
}

bool Network::connectToServer(const std::string& ip, int port) {
    if (client.connectToServer(ip, port)) {
        connected = true;
        return true;
    }
    return false;
}

void Network::disconnectFromServer() {
    if (connected) {
        client.disconnect();
        connected = false;
    }
}

void Network::checkNetworkEvents() {
    if (hosting) {
        server.handleConnections();
        // Handle other server-side events here if needed. Keep in mind "Heartbeat logic"
    }
    if (connected) {
        // Handle client-side events here if needed
    }
}

bool Network::isHosting() const {
    return hosting;
}

bool Network::isConnected() const {
    return connected;
}

