#include "player.hpp"
#include <memory>
#include <sstream>
#include <unistd.h>
#include <string.h>
#include "socket.hpp"
#include <exception>

Player::Player(){
    
}

vector<string> Player::split(string &s, char delim){
    vector<string> output;
    stringstream ss(s);
    string sub;
    
    while(getline(ss, sub, delim)){
        output.push_back(sub);
    }
    return output;
}

Player::Player(string name,int x, int y){
    this->name = name;
    this->x = x;
    this->y = y;
}

void Player::set_x(int x){
    this->x = x; 
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
     vector<string> data;
     string labelposition;
     linedata = this->split(line, ':'); //vector
     label = linedata.at(0);  //string
     this->name = label;  
     labelposition = linedata.at(1); //string
     data = this->split(labelposition, ',');
     
     try{
        this->x = stoi(data.at(0));
        this->y = stoi(data.at(1)); 
     }
     catch (...){
        cout << "std::invalid_argument" <<endl;
     }   
}

bool Player::check_in_line(Player Tem, Player Ball){
     // Tem = T, Ball = B, Robot = this: are in a straight line or not
     int RTx = Tem.get_x() - this->x;
     int RTy = Tem.get_y() - this->y;
     
     int RBx = Ball.get_x() - this->x;
     int RBy = Ball.get_y() - this->y;
     
     int BTx = Tem.get_x() - Ball.get_x();
     int BTy = Tem.get_y() - Ball.get_y();
     
     int kx = RTx - RBx - BTx;
     int ky = RTy - RBy - BTy;
     
     int RT = distance(Tem);
     int RB = distance(Ball);
     int BT = Ball.distance(Tem);
     int n = (RT - RB - BT);
     
     if(kx == 0 && ky == 0 && n <= 100 && RTx < 0 && RBx < 0 ){
         return true;
     }   
     return false;
}

void Player::update_attack_position(Player Ball){
     Player robot(this->name, this->x, this->y);
     Player Tem("t",0,0);
     Tem.set_x(4800 + int((Ball.get_x()-4800)*1.1));
     Tem.set_y(1650 + int((Ball.get_y()-1650)*1.1));
     int distance_RB = this->distance(Ball); // R = Robot, B = Ball
     cout<<"Distance between Robot and Ball: "<<distance_RB<<endl;
     int distance_RT = this->distance(Tem); // R = Robot, T = Temporary
     int distance_TB = Tem.distance(Ball); // T = Temporary, B = Ball
     cout<<"Distance between Tem and Ball: "<<distance_TB<<endl;
     
     Player Goal("0",4800,1650);
     Player Target("t",0,0);
     
     if(this->check_in_line(Tem,Ball)){ 
         cout<<"Ball, Tem, Robot are in the line"<<endl;
         
         this->x = Tem.get_x() + int(distance_TB*3*cos(3.14*2/3));
         this->y = Tem.get_y() + int(distance_TB*3*sin(3.14*2/3));
         
         cout<<"Get-in-line:--x-- "<< this->x <<"--y---"<< this->y <<endl;  
     }
     
     else{
        cout<<"Kicking_ball "<<endl;
        int triangle_TRB = Tem.get_x() * (robot.get_y() - Ball.get_y()) + robot.get_x() * (Ball.get_y() - Tem.get_y()) + Ball.get_x() * (Tem.get_y() - robot.get_y());
        
        cout<<"triangle_TRB: "<<triangle_TRB<<endl;
        if(distance_RT <= 10){
             cout<<"Kicking ball "<<endl;
             this->x = Ball.get_x();
             this->y = Ball.get_y();  
        }
        else{
             cout<<"Go to Temporary's position: "<<endl;
             this->x = Tem.get_x();
             this->y = Tem.get_y();
             if (abs(triangle_TRB) < 10*distance_TB){
                 this->x = Ball.get_x();
                 this->y = Ball.get_y();  
             }
        }
     } 
}

void Player::update_defense_position(Player Ball){
    this->x = int(0.7*Ball.get_x());
    this->y = 1650 + int(0.7*(Ball.get_y() - 1650));

    if(this->x >= 2400){
       this->x = 2200;
    }
}

void Player::update_prepare_position(Player Ball){
    this->x = Ball.get_x() - 300;
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






