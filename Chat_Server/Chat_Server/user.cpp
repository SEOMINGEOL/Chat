#include "ChatServer.h"
#include "user.h"

using namespace std;

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
		Broken_Connect(this);
		return;
	}

	length = strnlen(read_buf, 255);
	strncpy(buf, read_buf, strnlen(read_buf, 255));
	buf[length] = 0;
}

void User::CloseSocket()
{
	closesocket(this->user_sock);
}


void User::Work()
{
	char buf[255];

	while (true)
	{
		Read_Data(buf);
		log.PrintLog(buf);
	}
}

void User::Broken_Connect(User* user)
{
	//log.PrintOutUser(user);
	cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "가(이) 종료했습니다. 잘가요!" << endl;
	ChatServer temp;
	int length = temp.users.size();
	for (int i = 0; i < length ; i++)
	{
		if (user->GetSocket() == temp.users[i]->GetSocket())
		{
			temp.users.erase(temp.users.begin() + i);
			break;
		}
	}

	delete this;
	return;
}




void User::Send_Data(char* buf)
{
	
}


User::~User()
{
	CloseSocket();
}
