#include "ChatServer.h"
#include "Log.h"

static Log v_log;

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

	v_log.PrintLog("Start Server");
	while (true)
	{
		User* user = chat_server.Accept();
		ChatServer::users.push_back(user);
		v_log.PrintNewUser(user);
		//user->Work();
	}
}

