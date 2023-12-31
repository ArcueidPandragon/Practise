#include "channel.h"
#include "Epoll.h"
#include <unistd.h>
#include "error.h"
#include "eventLoop.h"
#define buff_size 1024


channel::channel(int fd,eventLoop* eventloop_):
	channelFd(fd),
	eventloop(eventloop_){}

channel::~channel(){}

void channel::connectFunction(){
	int strlen=0;
	char buf[buff_size];
	strlen=read(channelFd,buf,buff_size);
	if(strlen==0) handError("read error!\n");
	write(channelFd,buf,strlen);
}

void channel::add_channel() {eventloop->getEpoll()->addChannel(this);}
