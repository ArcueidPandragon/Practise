#include "channel.h"
#include "Epoll.h"
#include <unistd.h>
#define buff_size 1024


channel::channel(int fd):
	channelFd(fd){}

channel::channel():
	channelFd(0){}

channel::~channel(){}

void channel::connectFunction(){
	int strlen=0;
	char buf[buff_size];
	strlen=read(channelFd,buf,buff_size);
	if(strlen==0) handError("read error!\n");
	write(channelFd,buf,strlen);
}
