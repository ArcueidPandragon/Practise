#include "eventLoop.h"
#include "error.h"
#include "Epoll.h"
#include "channel.h"
#include <unistd.h>
#include <cstdint>
#include <sys/eventfd.h>
int creatfd(){
	int efd = eventfd(0, EFD_SEMAPHORE | EFD_CLOEXEC);
	if (efd==-1) handError("creatfd error!\n");
	return efd;
}


eventLoop::eventLoop():
		wakeUpfd_(creatfd),
		epoll_(new Epoll()),
		wakeChannel(new channel(wakeUpfd_)){
			wakeChannel->setEvent(EPOLLIN|EPOLLET);
			wakeChannel->setRead(std::bind(&eventLoop::hand_read,this));
		}

eventLoop::~eventLoop(){}


void eventLoop::queue_in(functor& func){
	{
	std::lock_guard<std::mutex> lock(Mutex);
	queue.emplace_back(func);
	}
}


void eventLoop::loop(){
	std::vector<channel*> waitHandle=epoll_->poll();
	for (auto&channel_:waitHandle) channel_->handleEvent();
	do_queue();
}


void eventLoop::do_queue(){
	std::vector<functor> working;
	{
	std::lock_guard<std::mutex> lock(Mutex);
	working.swap(queue);
	for (auto &work:working) work();
	}
}

void eventLoop::hand_read(){
	ssize_t size_;
	uint64_t int_=1;
	size_=read(wakeUpfd_, &int_, sizeof(int_));
	if (size_!=sizeof(int_)) handError("wakeup_read error!\n");
}

