#include "ChatServer.h"
#include "ThreadPool.h"

vector<User*> ChatServer::users = vector<User*>();
vector<thread> ChatServer::works = vector<thread>();
mutex ChatServer::mutex_users;
mutex ChatServer::mutex_thread;

ChatServer::ChatServer()
{
}


ChatServer::~ChatServer()
{
}

void ChatServer::Read_Data(char* buf, User* user)
{
	char read_buf[255];
	int length = 0;
	memset(&read_buf, 0, sizeof(read_buf));

	if (recv(user->GetSocket(), (char*)&read_buf, sizeof(read_buf), 0) <= 0)
	{
		throw 99;
	}

	length = strnlen(read_buf, 255);
	strncpy(buf, read_buf, strnlen(read_buf, 255));
	buf[length] = 0;
}

void ChatServer::Send_Data(const char* buf, SOCKET socket)
{
	char send_buf[255];
	memset(&send_buf, 0, sizeof(send_buf));

	if (buf != nullptr)
	{
		int length = strnlen(buf, 255);
		strncpy(send_buf, buf, length);
		send_buf[length] = 0;
	}

	if (send(socket, send_buf, sizeof(send_buf), 0) <= 0)
	{
		//log.PrintLog("Send Error");
	}
}

void ChatServer::SendMessageToUsers(const char* buf)
{
	int length = ChatServer::users.size();

	for (int i = 0; i < length; i++)
	{
		Send_Data(buf, ChatServer::users[i]->GetSocket());
	}
}

void ChatServer::SendMessageNickNameToUser(User* user, char* nickname)
{
	Send_Data(nickname, user->GetSocket());
}

void ChatServer::Start()
{
	chat_server.Bind();
	chat_server.Listen();

	log.PrintLog("Start Server");
	
	ThreadPool pool(3);

	while (true)
	{
		User* user = chat_server.Accept();

		if (users.size() >= 3) {
			log.PrintLog("최대 유저 초과");
			delete user;
			continue;
		}

		mutex_users.lock();
		ChatServer::users.push_back(user);
		mutex_users.unlock();

		pool.AddUser(user);
	}
}


