#pragma once
#include <vector>
#include "user.h"

using namespace std;

class ChatRoom
{
private:
	vector<User> users;
public:
	ChatRoom();
	~ChatRoom();
};

