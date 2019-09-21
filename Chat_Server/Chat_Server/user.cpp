#include "ChatServer.h"
#include "user.h"

User::User()
{
}

User::User(SOCKET user_sock, SOCKADDR_IN user_addr)
{
	this->user_sock = user_sock;
	this->user_address = user_addr;
	this->user_name = "Empty";
}

string User::GetUser_Name()
{
	return user_name;
}

SOCKET User::GetSocket()
{
	return this->user_sock;
}

SOCKADDR_IN User::GetSocket_Addr()
{
	return this->user_address;
}

void User::SetUser_Name(string name)
{
	this->user_name = name;
}

string User::GetUserIp()
{
	return inet_ntoa(this->user_address.sin_addr);
}


int User::GetUserPort()
{
	return user_address.sin_port;
}


void User::Read_Data(char* buf)
{
	char read_buf[255];
	int length = 0;
	memset(&read_buf, 0, sizeof(read_buf));

	if (recv(this->user_sock, (char*)&read_buf, sizeof(read_buf), 0) <= 0)
	{
		throw 99;
	}

	length = strnlen(read_buf, 255);
	strncpy(buf, read_buf, strnlen(read_buf, 255));
	buf[length] = 0;
}

void User::CloseSocket()
{
	closesocket(this->user_sock);
}


void User::Work(atomic<bool>* flag)
{
	char buf[255];
	string buf_str;
	while (true)
	{
		try 
		{
			Read_Data(buf);
			buf_str = buf;
			if (buf_str.length() > 0)
				log.PrintLog(buf_str);
		}
		catch (int e)
		{
			log.PrintOutUser(this);
			break;
		}
	}
	
	int length = ChatServer::users.size();
	
	ChatServer::mutex_users.lock();
	for (int i = 0; i < length; i++)
	{
		if (this->GetSocket() == ChatServer::users[i]->GetSocket())
		{
			ChatServer::users.erase(ChatServer::users.begin() + i);
			break;
		}
	}
	ChatServer::mutex_users.unlock();


	int len = ChatServer::works.size();
	cout << " " << len << endl;
	len = ChatServer::users.size();
	cout << " " << len << endl;
	*flag = true;

	delete this;
}

void User::Send_Data(char* buf)
{
	
}


User::~User()
{
	closesocket(this->user_sock);
	
	/*
	if (ChatServer::done)
	{
		cout << "over here" << endl;
		int len = ChatServer::works.size();
		cout << " " << len << endl;
		len = ChatServer::users.size();
		cout << " " << len << endl;
		ChatServer::mutex_thread.lock();
		ChatServer::works[0].detach();
		if (ChatServer::works[0].joinable())
		{
			cout << "asdfasdfasdf" << endl;
			ChatServer::works[0].join();
		}
		
		ChatServer::mutex_thread.unlock();
		cout << "end here" << endl;
	}
	*/
}
