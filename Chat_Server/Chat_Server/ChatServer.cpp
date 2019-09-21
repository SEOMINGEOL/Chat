#include "ChatServer.h"

vector<User*> ChatServer::users = vector<User*>();
vector<thread> ChatServer::works = vector<thread>();
mutex ChatServer::mutex_users;
mutex ChatServer::mutex_thread;
atomic<bool> ChatServer::done = false;

ChatServer::ChatServer()
{
}


ChatServer::~ChatServer()
{
}

void ChatServer::ThreadWorkFunc(User* user)
{
	//ChatServer::mutex_thread.lock();
	cout << "124124124" << endl;
	user->Work();
	cout << "124124124" << endl;
	
	delete user;
	//ChatServer::works.push_back(thread([&]() {user->Work(); }));
	//ChatServer::mutex_thread.unlock();
	
	cout << "124124124" << endl;
	done = true;
}

void ChatServer::Start()
{
	chat_server.Bind();
	chat_server.Listen();

	log.PrintLog("Start Server");

	while (true)
	{
		User* user = chat_server.Accept();

		mutex_users.lock();
		ChatServer::users.push_back(user);
		mutex_users.unlock();
		log.PrintNewUser(user);
		ChatServer::works.push_back(thread([&]() {ChatServer::ThreadWorkFunc(user); }));

		
		if (done)
		{
			cout << "finish" << endl;
			works[0].join();
			cout << "finish end" << endl;
		}
		
	}
}


