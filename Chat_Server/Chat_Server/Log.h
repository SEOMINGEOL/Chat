#pragma once

#ifndef LOG_CLASS
#define LOG_CLASS

#include <iostream>
#include <string>
#include <ctime>

class User;

using std::cout;
using std::endl;
using std::string;

class Log
{
private:
	time_t current_time;
	struct tm *current_tm;
public:
	Log();
	~Log();

	void PrintLog(string log);
	void Print_Time();
	void PrintNewUser(User* user);
	void PrintOutUser(User* user);
	
};

#endif // !LOG_CLASS