#pragma once

#ifndef THREAD_POOL
#define THREAD_POOL

#include <iostream>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>

#include "ChatServer.h"
#include "user.h"

using namespace std;
	
class ThreadPool : public ChatServer
{
private:
	size_t thread_num;
	vector<thread> users_thread;
	queue<User*> users_queue;
	condition_variable works_cv;
	mutex users_mutex;
public:
	ThreadPool(size_t thread_num);
	~ThreadPool();

	void ThreadPool::ThreadWorkFunc();
	void AddUser(User* user);
};


#endif //! ThreadPool
