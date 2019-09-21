#pragma once

#ifndef CHATSERVER_CLASS
#define CHATSERVER_CLASS

#include <iostream>
#include <vector>
#include "ChatSocket.h"
#include "user.h"

using std::cout;
using std::endl;
using std::vector;

class ChatServer
{
private:
	ChatSocket chat_server;
public:
	ChatServer();
	~ChatServer();

	void Start();
	vector<User*> users;
};

#endif // !CHATSERVER_CLASS