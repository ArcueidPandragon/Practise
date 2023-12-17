#include "acceptor.h"
#include "threadPool.h"

threadPool::threadPool(eventLoop* mainloop_,int threadNumber_):
	threadNumber(threadNumber_),
	mainloop(mainloop_),
	num(0){}


void threadPool::start(){
	for (int i=0;i<threadNumber;i++){
		thread_* thread=new thread_();
		threads.emplace_back(thread);	
		loops.emplace_back(thread->startloop());
	}
}

eventLoop* threadPool::nextloop(){
	eventLoop* next=loops[num];
	num=(num+1)%threadNumber;
	return next;
}
