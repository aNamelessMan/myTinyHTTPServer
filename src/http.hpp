#ifndef HTTP_HPP
#define HTTP_HPP

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "tool.hpp"

#define BUF_SIZE 1024
char buffer[BUF_SIZE];

char read_buf[BUF_SIZE];
/*读取http请求到read_buf*/
/*ubuntu上的firefox发出的网页请求大值如下
GET / HTTP/1.1
Host: localhost:54321
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0
Accept: text/html
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1

因此只需要将请求行中的URI和资源所在目录凭借就能得到本地路径
*/
void readin(int fd){
    memset(read_buf, '\0', BUF_SIZE);
    int read_idx = 0;//下一个读取的字符应该放在read_buf的该下标处
    int bytes_read = 0;
    while(true){
        bytes_read = recv(fd, read_buf + read_idx, BUF_SIZE - read_idx - 1, 0);
        if(bytes_read == -1){
            //对于非阻塞IO，下面的条件成立表示数据已经全部读取完毕
            if(errno == EAGAIN || errno == EWOULDBLOCK){
                break;
            }
            return;//如果是其他错误也暂时不作处理直接返回
        }
        read_idx += bytes_read;
    }
}

void processhttp(int fd){
    setnonblocking(fd);
    readin(fd);
}

//仅仅将受到的数据发送回去
void process(int connfd){
    memset(buffer, '\0', BUF_SIZE);

    int ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
    checkRetVal("recv", ret);
    printf("got %d bytes of normal data '\n%s'\n", ret, buffer);

    //ret = send(connfd, buffer, strlen(buffer), 0);
}

#endif