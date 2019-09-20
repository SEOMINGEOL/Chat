#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <string>
#include <WinSock2.h>
#include "Log.h"

using namespace std;

class User
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
	void Read_Data(char* buf);
	void Send_Data(char* buf);
	void Broken_Connect(User* user);
	void Work();
	void CloseSocket();
	string GetUser_Name();
	Log log;
};

