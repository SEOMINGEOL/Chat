#pragma once

#ifndef CHATROOM_CLASS
#define CHATROOM_CLASS


#include <vector>
#include "user.h"

using namespace std;

class ChatRoom
{
private:
	
public:
	ChatRoom();
	~ChatRoom();
	vector<User*> users;
};

#endif // !CHATROOM_CLASS