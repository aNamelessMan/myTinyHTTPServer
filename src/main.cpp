#include <iostream>
#include <netinet/in.h>
#include <assert.h>
#include <unistd.h>

#include "netWork.hpp"
#include "http.hpp"

using namespace std;

int main(){
    //Server端准备
    int listenfd = getListenfd("localhost", 54321);
    cout << "listenfd: " << listenfd << endl;

    //接受请求
    int connfd = getConnfd(listenfd);

    //处理请求
    while(1){
        process(connfd);
    }
    close(listenfd);
    close(connfd);
    
    //cout << "reach here" << endl;
}