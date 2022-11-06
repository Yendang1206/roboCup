#include "player.hpp"

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






