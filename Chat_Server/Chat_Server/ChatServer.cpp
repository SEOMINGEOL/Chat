#include "ChatServer.h"

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

void ChatServer::ThreadWorkFunc(User* user)
{
	char buf[255];
	string buf_str;
	while (true)
	{
		try
		{
			Read_Data(buf, user);
			buf_str = buf;
			if (buf_str.length() > 0)
			{
				log.PrintUserChat(user, buf_str);
				string send_buf = log.GetTime() + user->GetUserInfo() + string(buf);
				SendMessageToUsers(send_buf.c_str());
			}

		}
		catch (int e)
		{
			log.PrintOutUser(user);
			int length = ChatServer::users.size();

			ChatServer::mutex_users.lock();
			for (int i = 0; i < length; i++)
			{
				if (user->GetSocket() == ChatServer::users[i]->GetSocket())
				{
					ChatServer::users.erase(ChatServer::users.begin() + i);
					break;
				}
			}
			ChatServer::mutex_users.unlock();
			string send_buf = user->GetUserInfo() + "유저가 나갔습니다.";
			SendMessageToUsers(send_buf.c_str());
			break;
		}
	}
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

		thread thread_work = (thread([&]() {ChatServer::ThreadWorkFunc(user); }));
		thread_work.detach();
	}
}


