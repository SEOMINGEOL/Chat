#pragma once

#ifndef CHATSERVER_CLASS
#define CHATSERVER_CLASS

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "ChatSocket.h"
#include "user.h"
#include "Log.h"

using std::thread;
using std::cout;
using std::endl;
using std::vector;
using std::mutex;

class ChatServer : public Log
{
private:
	ChatSocket chat_server;
public:
	ChatServer();
	~ChatServer();

	void Start();
	void Read_Data(char* buf, User* user);
	void Send_Data(const char* buf, SOCKET socket);
	void SendMessageToUsers(const char* buf);
	void SendMessageNickNameToUser(User* user, char* buf);
	static vector<User*> users;
	static vector<thread> works;
	static mutex mutex_users;
	static mutex mutex_thread;
	Log log;
	
};

#endif // !CHATSERVER_CLASS