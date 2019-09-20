#include "Log.h"

Log::Log()
{
	current_time = time(NULL);
	current_tm = localtime(&current_time);
}


Log::~Log()
{
}

void Log::Print_Time()
{
	cout << current_tm->tm_year + 1900;
	cout.fill('0');
	cout.width(2);
	cout << current_tm->tm_mon + 1 << current_tm->tm_mday << current_tm->tm_hour << current_tm->tm_min << current_tm->tm_sec;
	cout << " : ";
}

void Log::PrintLog(string log)
{
	Print_Time();
	cout << log << endl;
}
/*
void Log::PrintNewUser(User* user)
{
	Print_Time();
	cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "가(이) 접속했습니다. 환영해주세요!" << endl;
}*/
/*
void Log::PrintOutUser(User* user)
{
	Print_Time();
	cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "가(이) 종료했습니다. 잘가요!" << endl;
}*/