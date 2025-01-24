#include "../include/Socket.h"

Socket::Socket() : sock(INVALID_SOCKET){}

Socket::~Socket() {
	close();
}

SOCKET Socket::getSocket() const
{
	return sock;
}

bool Socket::create(int type) {
	sock = socket(AF_INET, type, 0); // the 3rd parameter uses the default protocol for the declared type. 
	if (sock == INVALID_SOCKET) {
		// TODO: Give user a visible eror telling the socket creation is failed. WSAGetLastError() is better practice if used.
		return false;
	}
	return true;
}

bool Socket::bind(const std::string& ip, int port) {
	sockaddr_in addr = {};
	addr.sin_family = AF_INET; // ipv4
	addr.sin_port = htons(port); 
	inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

	if (::bind(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		// TODO: Give user a visible eror telling bind is failed. WSAGetLastError() is better practice if used.
		return false;
	}
	return true;

}

bool Socket::listen() {
	if (::listen(sock, SOMAXCONN) == SOCKET_ERROR) {
		// TODO: Give user a visible eror telling listen is failed. WSAGetLastError() is better practice if used.
		return false;
	}
	return true;
}

SOCKET Socket::accept()
{
	SOCKET clientSocket = ::accept(sock, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET) {
		// TODO: Give user a visible eror telling accept is failed. WSAGetLastError() is better practice if used.
	}
	return clientSocket;
}

bool Socket::connect(const std::string& ip, int port) {
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

	if (::connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		// TODO: Give user a visible eror telling connect is failed. WSAGetLastError() is better practice if used.
		return false;
	}
	return true;
}

int Socket::send(const std::string& message) {
	return ::send(sock, message.c_str(), message.length(), 0);
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
