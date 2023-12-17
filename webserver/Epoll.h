#pragma once
#include <sys/epoll.h>
#include <vector>
#include <unordered_map>
#include "channel.h"
class Epoll{
	private:
		int epollFd;
		std::vector<struct epoll_event> events;
		std::unordered_map<int,channel*> fd_channel;
	public:
		Epoll();
		~Epoll();
		void addChannel(channel*);
		std::vector<channel*> poll();
};
