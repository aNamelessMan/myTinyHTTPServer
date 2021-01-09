#ifndef NET_WORK_HPP
#define NET_WORK_HPP

#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <assert.h>

#include "tool.hpp"

struct sockaddr_in& getAddress(const char* ip, int port){
    struct sockaddr_in *paddress = new sockaddr_in;
    bzero(paddress, sizeof(*paddress));
    paddress->sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(paddress->sin_addr));
    paddress->sin_port = htons(port);
    return *paddress;
}

int getListenfd(const char* ip, int port){
    //获取填充了地址信息的sockaddr结构
    struct sockaddr_in &address = getAddress(ip, port);
    checkSockaddr(address);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    checkRetVal("socket", listenfd);

    setreuse(listenfd);

    int ret = 0;
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    checkRetVal("bind", ret);

    ret = listen(listenfd, 5);
    checkRetVal("listen", ret);

    return listenfd;
}

int getConnfd(int listenfd){
    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
    checkRetVal("accept", connfd);
    return connfd;
}

#endif