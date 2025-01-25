#include "../include/Network.h"
#include <Windows.h> // For MessageBoxA, Sleep

Network::Network()
    : hosting(false),
    connected(false)
{
}

Network::~Network() {
    cleanup();
}

bool Network::initialize() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        MessageBoxA(nullptr, "WSAStartup failed!", "Error", MB_OK);
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
        runServerThread = true;
        serverThread = std::thread(&Network::serverThreadFunc, this);
        return true;
    }
    return false;
}

void Network::stopServer() {
    if (!hosting) return;

    runServerThread = false;
    // stop the server (close the listening socket)
    server.stop();
    if (serverThread.joinable()) {
        serverThread.join();
    }
    hosting = false;
}

bool Network::connectToServer(const std::string& ip, int port) {
    if (client.connectToServer(ip, port)) {
        connected = true;
        runClientThread = true;
        clientThread = std::thread(&Network::clientThreadFunc, this);
        return true;
    }
    return false;
}

void Network::disconnectFromServer() {
    if (!connected) return;

    runClientThread = false;
    client.disconnect();
    if (clientThread.joinable()) {
        clientThread.join();
    }
    connected = false;
}

void Network::checkNetworkEvents() {
    // Pop messages from the queue and display or handle them
    std::string msg;
    while (getNextMessage(msg)) {
        MessageBoxA(nullptr, msg.c_str(), "Network Message", MB_OK);
    }
}

bool Network::getNextMessage(std::string& outMessage) {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (!messageQueue.empty()) {
        outMessage = messageQueue.front();
        messageQueue.pop();
        return true;
    }
    return false;
}

bool Network::isHosting() const {
    return hosting;
}

bool Network::isConnected() const {
    return connected;
}

void Network::sendMessageToAll(const std::string& message) {
    // If we are the host, broadcast
    if (hosting) {
        server.broadcast(message);
    }
    // If we are client only, send to server
    else if (connected) {
        client.sendMessage(message);
    }
}

void Network::pushMessage(const std::string& msg) {
    std::lock_guard<std::mutex> lock(queueMutex);
    messageQueue.push(msg);
}

// ----- THREADS -----

void Network::serverThreadFunc() {
    while (runServerThread) {
        // handleConnections() blocks on accept() until a client arrives
        server.handleConnections();
        // Once accept returns (client connected or error), we can loop again
        // If the listening socket was closed, accept() returns INVALID_SOCKET, so break
        if (!runServerThread) break;
    }
    pushMessage("Server thread ended.");
}

void Network::clientThreadFunc() {
    while (runClientThread) {
        std::string msg = client.receiveMessage();
        if (!msg.empty()) {
            pushMessage("From Server: " + msg);
        }
        else {
            // either closed or error
            Sleep(50);
        }
    }
    pushMessage("Client thread ended.");
}
