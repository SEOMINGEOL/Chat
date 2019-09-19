#pragma once
#include <vector>
#include "user.h"

using namespace std;

class ChatRoom
{
private:
	vector<user> member;
public:
	ChatRoom();
	~ChatRoom();
};

