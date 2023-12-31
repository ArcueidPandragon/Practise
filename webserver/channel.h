#pragma once
#include <functional>
#include <cstdint>
#include <sys/epoll.h>

class eventLoop;

class channel{
	private:
		typedef std::function<void()> callback;
		int channelFd;
		eventLoop* eventloop;

		uint32_t events;
		uint32_t revents;

		callback funcWrite;
		callback funcError;
		callback funcRead;
		callback funcClose;
		
	public:
		channel(int,eventLoop*);
		~channel();
		int getfd() {return channelFd;}
		int getevents() {return events;}
		eventLoop* getevent(){return eventloop;}

		void setWrite(callback&& func) {funcWrite=func;}
		void setError(callback&& func) {funcError=func;}
		void setRead(callback&& func) {funcRead=func;}
		void setClose(callback&& func) {funcClose=func;}
		void setLoop(eventLoop* eventloop_) {eventloop=eventloop_;}

		void handleWrite() { if(funcWrite) funcWrite();}
		void handleError() { if(funcError) funcError();}
		void handleRead() { if(funcRead) funcRead();}
		void handleClose() { if(funcClose) funcClose();}

		void setEvent(uint32_t input) {events=input;}
		void setRevents(uint32_t input) {revents=input;}
		void setFd(int input) {channelFd=input;}

		void handleEvent() {
			if ((revents & EPOLLHUP) && !(revents & EPOLLIN))  return;
			if (revents & EPOLLERR) {
				handleError();
  				return;
				}
			if (revents & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
  				handleRead();
				}
			if (revents & EPOLLOUT) {
  				handleWrite();
				}
		}

		void connectFunction();
		void add_channel();


};
