#ifndef HTTP_HPP
#define HTTP_HPP

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "tool.hpp"

#define BUF_SIZE 64
//仅仅将受到的数据发送回去
void process(int connfd){
    char buffer[BUF_SIZE];
    memset(buffer, '\0', BUF_SIZE);

    int ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
    checkRetVal("recv", ret);
    printf("got %d bytes of normal data '%s'\n", ret, buffer);

    ret = send(connfd, buffer, strlen(buffer), 0);
}

#endif