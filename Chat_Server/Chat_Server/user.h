#pragma once

#include <string>
#include <WinSock2.h>

using namespace std;

class user
{
private:
	SOCKET client_sock;
	SOCKADDR_IN client_address;
	string user_name;
public:
	user();
	~user();
	user(SOCKET client_sock, SOCKADDR_IN client_addr);
	SOCKET getSocket();
	SOCKADDR_IN getSocket_addr();
	string getuserip();
	int getuserport();
	void setUser_name(string user_name);
	string getuser_name();
};

