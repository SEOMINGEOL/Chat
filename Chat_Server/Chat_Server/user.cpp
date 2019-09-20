#include "user.h"

using namespace std;

User::User()
{
}

User::User(SOCKET client_sock, SOCKADDR_IN client_addr)
{
	this->client_sock = client_sock;
	this->client_address = client_addr;
}

string User::GetUser_Name()
{
	return user_name;
}

SOCKET User::GetSocket()
{
	return this->client_sock;
}

SOCKADDR_IN User::GetSocket_Addr()
{
	return this->client_address;
}

void User::SetUser_Name(string name)
{
	this->user_name = name;
}

string User::GetUserIp()
{
	return inet_ntoa(this->client_address.sin_addr);
}

int User::GetUserPort()
{
	return client_address.sin_port;
}

User::~User()
{
}
