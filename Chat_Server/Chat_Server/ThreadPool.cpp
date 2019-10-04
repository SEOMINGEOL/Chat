#include "ThreadPool.h"


ThreadPool::ThreadPool(size_t thread_num)
{
	this->thread_num = thread_num;
	users_thread.reserve(thread_num);
	for (size_t i = 0; i < thread_num; i++)
	{
		users_thread.emplace_back(thread([&]() {ThreadPool::ThreadWorkFunc(); }));
	}
}

ThreadPool::~ThreadPool()
{
	works_cv.notify_all();

	for (auto& t : users_thread)
	{
		t.join();
	}
}

void ThreadPool::ThreadWorkFunc()
{
	char buf[255];
	string buf_str;
	while (true)
	{
		unique_lock<mutex> lock(users_mutex);

		works_cv.wait(lock, [this]() { return !this->users_queue.empty(); });

		User* user = move(users_queue.front());
		users_queue.pop();
		lock.unlock();

		log.PrintNewUser(user);
		log.PrintNowUser();
		while (true)
		{
			try
			{
				Read_Data(buf, user);
				buf_str = buf;
				if (buf_str.length() > 0)
				{
					if (buf[0] == '*')
					{
						user->SetUser_Name(buf + 1);
						log.PrintUserChat(user, "닉네임 변경 완료되었습니다.");
						string send_buf = log.GetTime() + user->GetUserInfo() + "닉네임 변경이 완료되었습니다.";
						SendMessageNickNameToUser(user, buf);
						SendMessageToUsers(send_buf.c_str());
					}
					else
					{
						log.PrintUserChat(user, buf_str.erase(0, 1));
						string send_buf = log.GetTime() + user->GetUserInfo() + buf_str;
						SendMessageToUsers(send_buf.c_str());
					}
				}

			}
			catch (int e)
			{
				log.PrintOutUser(user);
				int length = ChatServer::users.size();

				ChatServer::mutex_users.lock();
				for (int i = 0; i < length; i++)
				{
					if (user->GetSocket() == ChatServer::users[i]->GetSocket())
					{
						ChatServer::users.erase(ChatServer::users.begin() + i);
						break;
					}
				}
				log.PrintNowUser();
				ChatServer::mutex_users.unlock();
				string send_buf = user->GetUserInfo() + "유저가 나갔습니다.";
				SendMessageToUsers(send_buf.c_str());
				break;
			}
		}

		delete user;
	}
}

void ThreadPool::AddUser(User* user)
{
	{
		lock_guard<mutex> lock(users_mutex);
		users_queue.push(move(user));
	}
	works_cv.notify_one();
}