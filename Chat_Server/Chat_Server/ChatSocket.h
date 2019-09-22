#pragma once

#ifndef CHATSOCKET_CLASS
#define CHATSOCKET_CLASS


#include <WinSock2.h>
#include "user.h"
#include "Log.h"

class ChatSocket : public Log
{
private:
	SOCKET server_socket;
	SOCKADDR_IN server_addr;
public:
	ChatSocket();
	~ChatSocket();

	void Bind();
	void Listen();

	User* Accept();
	Log log;
};

#endif // !CHATSOCKET_CLASS