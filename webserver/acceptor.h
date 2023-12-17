#pragma once
#include "eventLoop.h"
#include "channel.h"
#include "threadPool.h"
#include <cstdint>
class acceptor{
	private:
		eventLoop* mainLoop;
		channel* server;
		threadPool* threadpool;
		int fd;
		int port;
		int threadNumber;
	public:
		acceptor(eventLoop*,int port,int threadNumber);
		~acceptor();
		void handleConnect();
		void start();
		void connectFunction();
};
