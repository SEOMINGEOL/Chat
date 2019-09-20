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
		cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "��(��) �����߽��ϴ�. ȯ�����ּ���!" << endl;
		user->Work();
	}
}

