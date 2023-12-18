#ifndef NETWORK
#define NETWORK
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <unistd.h>
#include "socket.hpp"
using namespace std;

class Network {
private:
    string ip;
    string port;
    unique_ptr<Socket> sock = make_unique<Socket>(AF_INET,SOCK_STREAM,0);  
public:
    Network();
    Network(string ip, string port);
    string get_message(string position);
    void close_connect();
    ~Network();
};
#endif

