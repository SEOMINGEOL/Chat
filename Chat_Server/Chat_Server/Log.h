#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "user.h"

using namespace std;
class Log
{
private:
	time_t current_time;
	struct tm *current_tm;
public:
	Log();
	~Log();

	void PrintLog(string log);
	void PrintNewUser(User* user);
	void Print_Time();
	//void PrintOutUser(User* user);

};

