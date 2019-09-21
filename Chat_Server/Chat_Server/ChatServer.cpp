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

		mutex_thread.lock();		
		ChatServer::works.push_back(thread([&]() {user->Work(&done); }));
		mutex_thread.unlock();


		
		if (done)
		{
			cout << "finish" << endl;
			works[0].join();
		}
		
	}


}


