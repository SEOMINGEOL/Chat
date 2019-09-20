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

	while (true)
	{
		User* user = chat_server.Accept();
		users.push_back(user);
		cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "가(이) 접속했습니다. 환영해주세요!" << endl;
	}
}

