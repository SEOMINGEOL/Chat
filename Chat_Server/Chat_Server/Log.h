#pragma once
#include <iostream>
#include <string>
#include <ctime>

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
	void Print_Time();
};

