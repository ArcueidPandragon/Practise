#include "acceptor.h"
#include "eventLoop.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

acceptor::acceptor(eventLoop* loop_,int port_,int Number):
	mainLoop(loop_),
	server(new channel()),
	threadNumber(Number),
	port(port_),
	threadpool(new threadPool(loop_,Number)),
	fd(create_socket_listen(port_)){
		server->setFd(fd);
	}


acceptor::~acceptor(){}


void acceptor::start(){
	server->setEvent(EPOLLIN|EPOLLET);
	server->setRead(std::bind(&acceptor::handleConnect,this));
	mainLoop->epoll->addChannel(server);
	threadpool->start();
}


void acceptor::handleConnect(){
	int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
	if ((client_socket = accept(fd, (struct sockaddr*)&client_address, &client_address_len)) == -1)
		handError("acceptsocket error!\n");
    channel* connected=new channel(client_socket);
	connected->setEvent(EPOLLIN|EPOLLET);
	connected->setRead(std::bind(&channel::connectFunction,connected));
	eventLoop* next=threadpool->nextloop();
	next->queue_in(std::bind(&eventLoop::add_channel,next,connected));
	ssize_t size_;
	uint64_t int_=1;
	size_=write(connected->getfd(), &int_, sizeof(int_));
	if (size_!=sizeof(int_)) handError("wakeup_write error!\n");
}
