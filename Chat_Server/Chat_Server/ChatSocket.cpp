#include "ChatSocket.h"


ChatSocket::ChatSocket()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	this->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->server_socket == INVALID_SOCKET)
	{
		log.PrintLog("Socket OPEN Failed");
		WSACleanup();
	}

	this->server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	this->server_addr.sin_port = htons(5678);
	this->server_addr.sin_family = AF_INET;
}


ChatSocket::~ChatSocket()
{
	closesocket(this->server_socket);
	WSACleanup();
}


void ChatSocket::Bind()
{
	if (bind(this->server_socket, (SOCKADDR*)&this->server_addr, sizeof(this->server_addr)) == SOCKET_ERROR)
	{
		log.PrintLog("Bind Error");
	}
}

void ChatSocket::Listen()
{
	if (listen(this->server_socket, 10) == SOCKET_ERROR)
	{
		log.PrintLog("Listen Error");
	}
}

User* ChatSocket::Accept()
{
	SOCKET user_socket;
	SOCKADDR_IN user_addr;

	int length = sizeof(user_addr);

	user_socket = accept(this->server_socket, (SOCKADDR*)&user_addr, &length);

	return new User(user_socket, user_addr);
}