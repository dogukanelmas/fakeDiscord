#pragma once

#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>

class Socket {
public:
	Socket();
	~Socket();

	SOCKET getSocket() const;

	bool create(int type = SOCK_STREAM);
	bool bind(const std::string& ip, int port);
	bool listen();
	SOCKET accept();
	bool connect(const std::string& ip, int port);
	int send(const std::string& message);
	int receive(char* buffer, int length);

	void close();

private:
	SOCKET sock;
};