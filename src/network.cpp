#include "network.hpp"


Network::Network(){

}
    
Network::Network(string ip, string port){
    this->ip = ip;
    this->port = port;
    this->sock->connect(ip, port);
} 

string Network::get_message(string position){
    string buffer;
    this->sock->socket_write(position);
    this->sock->socket_read(buffer,1024);
    sleep(0.5);
    return buffer;
}


    
Network::~Network(){

}
