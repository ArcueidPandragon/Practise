#include "thread_.h"
#include <thread>
#include <functional>

thread_::thread_(){}


eventLoop* thread_::startloop(){
	loop=new eventLoop();
	std::thread running_thread(std::bind(&eventLoop::loop,loop));
	return loop;
}


