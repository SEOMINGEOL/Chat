#pragma once
#pragma comment(lib, "ws2_32.lib")

#ifndef USER_CLASS
#define USER_CLASS

#include <iostream>
#include <string>
#include <WinSock2.h>
#include "Log.h"

using std::cout;
using std::endl;
using std::string;


class User : public Log
{
private:
	SOCKET user_sock;
	SOCKADDR_IN user_address;
	string user_name;
public:
	User();
	~User();
	User(SOCKET user_sock, SOCKADDR_IN user_addr);
	SOCKET GetSocket();
	SOCKADDR_IN GetSocket_Addr();
	string GetUserIp();
	int GetUserPort();
	void SetUser_Name(string user_name);
	string GetUserInfo();
	void CloseSocket();
	string GetUser_Name();

	Log log;
	bool d_flag;
};



#endif // !USER_CLASS