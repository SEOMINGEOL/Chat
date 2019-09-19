#include "user.h"

using namespace std;

user::user()
{
}

user::user(SOCKET client_sock, SOCKADDR_IN client_addr)
{
	this->client_sock = client_sock;
	this->client_address = client_addr;
}

string user::getuser_name()
{
	return user_name;
}

SOCKET user::getSocket()
{
	return this->client_sock;
}

SOCKADDR_IN user::getSocket_addr()
{
	return this->client_address;
}

void user::setUser_name(string name)
{
	this->user_name = name;
}

string user::getuserip()
{
	return inet_ntoa(this->client_address.sin_addr);
}

int user::getuserport()
{
	return client_address.sin_port;
}

user::~user()
{
}
