#pragma once
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

