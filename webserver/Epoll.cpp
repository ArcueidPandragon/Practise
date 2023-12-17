#include "Epoll.h"
#include "error.h"
#include <vector>
#define max_size 50
Epoll::Epoll():
	events(max_size),
	epollFd(epoll_create())
	{
		if(epollFd==-1)	handError("epoll_create() error!");
	}

Epoll::~Epoll(){}

void Epoll::addChannel(channel* ptrChannel){
	struct epoll_event event;
	event.data.fd=ptrChannel->channelFd;
	event.events=ptrChannel->events;
	if(epoll_ctl(epollFd,EPOLL_CTL_ADD,ptrChannel->channelFd,&event)==-1) 
		handError("epoll_ctl() error!");
	fd_channel.emplace(epollFd,ptrChannel);
}

std::vector<channel*> Epoll::poll(){
	int eventNum=epoll_wait(epollFd,&events[0],max_size,-1);
	if (eventNum==-1) handError("epoll_wait() error!");
	std::vector<channel*> eventsChannel;
	for (int i=0;i<eventNum;i++){
		channel* channel_=fd_channel[events[i].data.fd];
		eventsChannel.push_back(channel_);
		channel_->setRevents(events[i].events);
	}
	return eventsChannel;
}
	
