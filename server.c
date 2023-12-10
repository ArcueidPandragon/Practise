#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
void error(char* message);


int main(int argc,char* argv[]){
	int server;
	int clinet;
        char message[]="Hello world";
	struct sockaddr_in server_addr;
	struct sockaddr_in clinet_addr;
	socklen_t clnt_addr_size;
	
	if (argc!=2) {
		error("please enter proper argument <port> <ipaddr>.");
		exit(1);}

	server=socket(PF_INET,SOCK_STREAM,0);
	if (server==-1) error("socket() error.");

	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1) 
		error("bind() error");

	if(listen(server,5)==-1) error("listrn() error");
        
	clnt_addr_size=sizeof(clinet_addr);
	clinet=accept(server,(struct sockaddr*)&clinet_addr,&clnt_addr_size);
	if(clinet==-1) error("accept() error");

	write(clinet,message,sizeof(message));
	close(server);
	close(clinet);
	printf("congratulation \n");
	
}


void error(char* message){
        fprintf(stderr,"%s\n",message);
        exit(1);
}

