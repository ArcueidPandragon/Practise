#include "eventLoop.h"
#include "error.h"
#include "acceptor.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc,char* argv[]){
	int opt;
	const char* str="p:n:";
	int port;
	int threadNumber;

	while((opt=getopt(argc,argv,str))!=-1){
	switch(opt){
		case 'p':{
			port=atoi(optarg);
			printf("port:%d\n",port);
			break;
			}
		case 'n':{
			threadNumber=atoi(optarg);
			printf("threadNumber:%d\n",threadNumber);
			break;
			}
		case '?': handError("argument error!");
		}
	}
	

	eventLoop mainLoop;
	acceptor Webserver(&mainLoop,port,threadNumber);
	Webserver.start();
	mainLoop.loop();

}
