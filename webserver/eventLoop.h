#pragma once
#include "Epoll.h"
#include "channel.h"
#include <functional>
#include <vector>
#include <mutex>

class eventLoop{
	private:
		typedef std::function<void()> functor;
		Epoll* epoll_;
		int wakeUpfd_;
		channel* wakeChannel;
		std::vector<functor> queue;
		std::mutex Mutex;
	public:
		eventLoop();
		~eventLoop();
		void loop();
		int getWakeFd() {return wakeUpfd_;}
		Epoll* getEpoll() {return epoll_;}
		void queue_in(functor&& func);
		void do_queue();
		void hand_read();
};

