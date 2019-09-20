#pragma once

#include <string>
#include <WinSock2.h>

using namespace std;

class User
{
private:
	SOCKET client_sock;
	SOCKADDR_IN client_address;
	string user_name;
public:
	User();
	~User();
	User(SOCKET client_sock, SOCKADDR_IN client_addr);
	SOCKET GetSocket();
	SOCKADDR_IN GetSocket_Addr();
	string GetUserIp();
	int GetUserPort();
	void SetUser_Name(string user_name);
	string GetUser_Name();
};

