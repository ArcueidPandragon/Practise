#include "thread_.h"
#include <thread>

thread_::thread_(){}


eventLoop* thread_::startloop(){
	loop=new eventLoop();
	std::thread running_thread(loop->loop());
	return loop;
}


