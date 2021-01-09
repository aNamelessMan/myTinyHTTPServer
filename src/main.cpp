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
    
    //注意此时只能处理一次连接，因为只调用了一次accept

    //接受请求
    int connfd = getConnfd(listenfd);

    //处理请求
    while(1){
        processhttp(connfd);
        if(read_buf[0] != '\0'){
            cout << "read_buf:" << endl;
            cout << read_buf << endl;
        }
        break;
    }

    close(listenfd);
    close(connfd);
    
    //cout << "reach here" << endl;
}