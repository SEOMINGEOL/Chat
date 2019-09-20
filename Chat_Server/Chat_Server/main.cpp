#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib, "ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <vector>
#include "user.h"

using namespace std;

int main(void)
{
	SOCKET server_sock, temp_sock;
	SOCKADDR_IN server_addr = { 0 }, temp_addr = { 0 };
	WSADATA wsaData;
	vector<User*> users;
	int len;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == INVALID_SOCKET)
	{
		cout << "Socket Open Failed" << endl;
		WSACleanup();
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(3490);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(server_sock, (SOCKADDR*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		cout << "Bind Error" << endl;
	}

	if (listen(server_sock, 10) == SOCKET_ERROR)
	{
		cout << "Socket Error" << endl;
	}

	len = sizeof(temp_addr);
	temp_sock = accept(server_sock, (SOCKADDR*)&temp_addr, &len);

	if (temp_sock == SOCKET_ERROR)
	{
		cout << "accept Error" << endl;
	}
	users.push_back(new User(temp_sock, temp_addr));

	cout << "Client Connect" << endl;
	cout << "ip : " << users[0]->GetUserIp() << " " << "port : " << users[0]->GetUserPort() << endl;

	closesocket(temp_sock);
	closesocket(server_sock);
	WSACleanup();
}