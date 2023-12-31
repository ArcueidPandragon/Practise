#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "error.h"
#define BACKLOG 5

int create_socket_listen(int port){
    int server_socket;
    struct sockaddr_in server_address;

    // 创建套接字
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        handError("creatsocket error!\n");

    // 设置服务器地址结构
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    // 绑定套接字
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
		handError("creatsocket error!\n");

    // 监听套接字
    if (listen(server_socket, BACKLOG) == -1)
		handError("listensocket error!\n");
    
	return server_socket;
}

