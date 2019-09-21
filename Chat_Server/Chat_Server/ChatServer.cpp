#include "ChatServer.h"

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
		ChatServer::users.push_back(user);
		log.PrintNewUser(user);
		//user->Work();
	}
}

