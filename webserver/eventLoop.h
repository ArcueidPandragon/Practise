#pragma once
#include "Epoll.h"
#include "channel.h"
#include <functional>
#include <vector>
#include <mutex>

class eventLoop{
	private:
		Epoll* epoll_;
		int wakeUpfd_;
		channel* wakeChannel;
		std::vector<functor> queue;
		std::mutex Mutex;
	public:
		typedef std::function<void()> functor;
		eventLoop();
		~eventLoop();
		void loop();
		int getWakeFd() {return wakeUpfd_;}
		void queue_in(functor&);
		void do_queue();
		void hand_read();
		void add_channel(channel* channel_) {epoll_->addChannel(channel_);}
};

