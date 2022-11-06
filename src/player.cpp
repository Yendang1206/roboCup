#include "player.hpp"
#include <memory>
#include <sstream>
#include <unistd.h>
#include <string.h>
#include "socket.hpp"

Player::Player(){
    
}

Player::Player(string name,int x, int y){
    this->name = name;
    this->x = x;
    this->y = y;
}

void Player::set_x(int x){
    this->x = x; //this->x: toa do cua player, x: toa do cua player khac
}
void Player::set_y(int y){
    this->y = y;
}

void Player::set_xy(int x,int y){
    this->x = x;
    this->y = y;
}

void Player::set_linedata(string line){
     
     string label;
     vector<string> linedata;
     string labelposition;
     
     
     cout<<"line thu 1: "<<line<<endl;
        
     linedata = split2(line, ':'); //vector
     label = linedata.at(0);  //string
     this->name = label;  
     cout<<"lable cua dong thu 1: "<<label<<endl;
     labelposition = linedata.at(1); //string
     data = split2(labelposition, ',');
     
     this->x = stoi(data.at(0));
     this->y = stoi(data.at(1)); 
     
}

double Player::distance(int x, int y){
    return sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y));
}
double Player::distance(Player another){
    return distance(another.get_x(), another.get_y());
}

int Player::get_x(void){
    return this->x;
}
int Player::get_y(void){
    return this->y;
}

string Player::get_name(void){
    return this->name;
}

string Player::get_position(void){
    string position;
    position = this->name + "," + to_string(this->x) + "," + to_string(this->y) + "\n";
    return position;
}

        
Player::~Player(){
    
}






