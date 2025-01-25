#pragma once

#include "Server.h"
#include "Client.h"
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>

class Network {
public:
    Network();
    ~Network();

    bool initialize();
    void cleanup();

    // Server
    bool startServer(const std::string& ip, int port);
    void stopServer();

    // Client
    bool connectToServer(const std::string& ip, int port);
    void disconnectFromServer();

    // Called by main thread each frame if desired
    void checkNetworkEvents();

    // Thread-safe queue for incoming messages
    bool getNextMessage(std::string& outMessage);

    bool isHosting() const;
    bool isConnected() const;

    // So the main app can call broadcast or client.send
    void sendMessageToAll(const std::string& message);

private:
    void serverThreadFunc();
    void clientThreadFunc();

    void pushMessage(const std::string& msg);

private:
    Server server;
    Client client;

    std::thread serverThread;
    std::thread clientThread;
    std::atomic<bool> runServerThread{ false };
    std::atomic<bool> runClientThread{ false };

    bool hosting;
    bool connected;

    std::queue<std::string> messageQueue;
    std::mutex queueMutex;
};
