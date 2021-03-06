#ifndef TOOL_HPP
#define TOOL_HPP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>

void checkSockaddr(struct sockaddr_in &address){
    char *ip = inet_ntoa(address.sin_addr);
    std::cout << "ip  : " << ip << std::endl;
    std::cout << "port: " << ntohs(address.sin_port) << std::endl;
}

void checkRetVal(const char* func , int ret){
    if(ret < 0){
        std::cout << "1.[function name] " << func << " 2.[error info] " << strerror(errno) << " 3.[retVal] " << ret << std::endl;
        exit(0);
    }
}

int setnonblocking(int fd){
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void setreuse(int fd){
    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
}

#endif