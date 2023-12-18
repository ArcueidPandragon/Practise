#include <vector>
#include "thread_.h"
#include "eventLoop.h"

class threadPool{
	private:
		eventLoop* mainloop;
		int threadNumber;
		int num;
		std::vector<thread_*> threads;
		std::vector<eventLoop*> loops;
		
	public:
		threadPool(eventLoop* acceptor_,int threadNumber_);
		void start();
		eventLoop* nextloop();
};
