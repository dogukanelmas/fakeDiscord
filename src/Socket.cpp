#include "../include/Socket.h"
#include <Windows.h>

Socket::Socket() : sock(INVALID_SOCKET) {}

Socket::~Socket() {
    close();
}

SOCKET Socket::getSocket() const {
    return sock;
}

void Socket::setSocket(SOCKET s) {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    sock = s;
}

bool Socket::create(int type) {
    sock = socket(AF_INET, type, 0);
    if (sock == INVALID_SOCKET) {
        MessageBoxA(nullptr, "Socket creation failed!", "Error", MB_OK);
        return false;
    }
    return true;
}

bool Socket::bind(const std::string& ip, int port) {
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    if (::bind(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        MessageBoxA(nullptr, "Socket bind failed!", "Error", MB_OK);
        return false;
    }
    return true;
}

bool Socket::listen() {
    if (::listen(sock, SOMAXCONN) == SOCKET_ERROR) {
        MessageBoxA(nullptr, "Socket listen failed!", "Error", MB_OK);
        return false;
    }
    return true;
}

SOCKET Socket::accept() {
    SOCKET clientSocket = ::accept(sock, nullptr, nullptr);
    return clientSocket;
}

bool Socket::connect(const std::string& ip, int port) {
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    if (::connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        MessageBoxA(nullptr, "Connect failed!", "Error", MB_OK);
        return false;
    }
    return true;
}

int Socket::send(const std::string& message) {
    return ::send(sock, message.c_str(), (int)message.size(), 0);
}

int Socket::receive(char* buffer, int length) {
    return ::recv(sock, buffer, length, 0);
}

void Socket::close() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}
