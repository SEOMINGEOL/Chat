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

string User::GetUserInfo()
{
	string user_info;
	user_info = this->GetUser_Name() + "(" + this->GetUserIp() + ", " + std::to_string(this->GetUserPort()) + ")" + " : ";

	return user_info;
}

void User::CloseSocket()
{
	closesocket(this->user_sock);
}

User::~User()
{
	CloseSocket();
}
