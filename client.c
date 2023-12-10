#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
void error(char* message);


int main(int argc,char* argv[]){
	int server;
        char message[30];
	struct sockaddr_in server_addr;
	socklen_t server_addr_size;
	
	if (argc!=3) {
		error("please enter proper argument <port> <ipaddr>.");
		exit(1);}

	server=socket(PF_INET,SOCK_STREAM,0);
	if (server==-1) error("socket() error.");

	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr=inet_addr(argv[2]);
       
	server_addr_size=sizeof(server_addr);
	if(connect(server,(struct sockaddr*)&server_addr,server_addr_size)==-1)
	error("connect() error");

	read(server,message,sizeof(message));
	fputs(message,stdout);
	close(server);
	
}

void error(char* message){
        fprintf(stderr,"%s\n",message);
        exit(1);
}
