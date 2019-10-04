#include "Log.h"
#include "user.h"
#include "ChatServer.h"

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
	current_time = time(NULL);
	current_tm = localtime(&current_time);

	cout << "[";
	cout << current_tm->tm_year + 1900;
	cout.fill('0');
	cout.width(2);
	cout << current_tm->tm_mon + 1;

	cout.fill('0');
	cout.width(2);
	cout << current_tm->tm_mday;

	cout.fill('0');
	cout.width(2);
	cout << current_tm->tm_hour;

	cout.fill('0');
	cout.width(2);
	cout << current_tm->tm_min;

	cout.fill('0');
	cout.width(2);
	cout << current_tm->tm_sec;
	cout << "] ";
}

string Log::GetTime()
{
	std::stringstream str_current_time;
	current_time = time(NULL);
	current_tm = localtime(&current_time);

	str_current_time << "[";
	str_current_time << current_tm->tm_year + 1900;
	str_current_time.fill('0');
	str_current_time.width(2);
	str_current_time << current_tm->tm_mon + 1;

	str_current_time.fill('0');
	str_current_time.width(2);
	str_current_time << current_tm->tm_mday;

	str_current_time.fill('0');
	str_current_time.width(2);
	str_current_time << current_tm->tm_hour;

	str_current_time.fill('0');
	str_current_time.width(2);
	str_current_time << current_tm->tm_min;

	str_current_time.fill('0');
	str_current_time.width(2);
	str_current_time << current_tm->tm_sec;
	str_current_time << "] ";

	return str_current_time.str();
}

void Log::PrintLog(string log)
{
	Print_Time();
	cout << log << endl;
}

void Log::PrintNewUser(User* user)
{
	Print_Time();
	cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "가(이) 접속했습니다. 환영해주세요!" << endl;
}

void Log::PrintUserChat(User* user, string log)
{
	Print_Time();
	cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << " : " << log << endl;
}

void Log::PrintOutUser(User* user)
{
	Print_Time();
	cout << user->GetUser_Name() << "(" << user->GetUserIp() << ", " << user->GetUserPort() << ")" << "가(이) 종료했습니다. 잘가요!" << endl;
}

void Log::PrintNowUser()
{
	Print_Time();
	cout << "현재 유저 수 : " << ChatServer::users.size() << endl;
}

