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
    this->sock->socket_read(buffer,4000);
    //sleep(0.02);
    return buffer;
}

void Network::close_connect(){
    this->sock->close(); 
}
    
Network::~Network(){

}
