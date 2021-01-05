#include <iostream>
#include "netWork.hpp"
#include "tool.hpp"

using namespace std;

int main(){
    //getAddress
    struct sockaddr_in &address = getAddress("192.168.0.1", 54321);
    checkSockaddr(address);
}