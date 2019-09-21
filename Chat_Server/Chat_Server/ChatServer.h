#pragma once

#ifndef CHATSERVER_CLASS
#define CHATSERVER_CLASS

#include <iostream>
#include <vector>
#include "ChatSocket.h"
#include "user.h"
#include "Log.h"

using std::cout;
using std::endl;
using std::vector;

class ChatServer : public Log
{
private:
	ChatSocket chat_server;
public:
	ChatServer();
	~ChatServer();

	void Start();
	vector<User*> users;
	Log log;
};

#endif // !CHATSERVER_CLASS