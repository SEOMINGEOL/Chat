#pragma once
#include <iostream>
#include <vector>
#include "ChatSocket.h"
#include "user.h"
#include "Log.h"


using namespace std;

class ChatServer
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
