#pragma once

#ifndef CHATSERVER_CLASS
#define CHATSERVER_CLASS

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include <atomic>
#include "ChatSocket.h"
#include "user.h"
#include "Log.h"

using std::thread;
using std::cout;
using std::endl;
using std::vector;
using std::mutex;
using std::atomic;
using std::future;

class ChatServer : public Log
{
private:
	ChatSocket chat_server;
public:
	ChatServer();
	~ChatServer();

	void Start();
	static vector<User*> users;
	static vector<thread> works;
	static mutex mutex_users;
	static mutex mutex_thread;
	Log log;
	static atomic<bool> done;
};

#endif // !CHATSERVER_CLASS