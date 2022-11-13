#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <unistd.h>
#include "socket.hpp"
#include "player.hpp"
#include "network.hpp"
#include "parser.hpp"


using namespace std;





int main(int argc, char *argv[]){
    
    Network network("localhost", "10000");
    
    string buffer;
    string position1 = "B:1000,2000";
    //Parser::parse(datass);
    Parser parser;
    
    
   
    Player B("b",0,0);
    Player R1("1",0,0);
    Player R2("2",0,0);
    Player R3("3",0,0);
    Player R4("4",0,0);
    Player R5("5",0,0);
    
    Player Tem("t",0,0);
    
    //cout<<R3.get_x()<<endl;
    //cout<<R3.get_y()<<endl;
    //cout<<"Khoang cach R3: "<<R3.distance(R4)<<endl;
    //cout<<"Robot number "<<R3.get_name()<<endl;
    //cout<<"--------------------"<<endl;
   
    
    
    string position = "3,0,1000\n"; //toa do Goal
    
    string Temporary = "3,x1,y1";
    
    //doc toa do cua cac robot, ball -> gan nhat -> chay toi toa do temporary -> sut bong
    //if khong gan ball -> tiep tuc di chuyen tip toi temporary -> sut bong
    
    //toa do ball -> tinh toa do temporary -> tim khoang cach cua con robot nao gan nhat vs toa do temporary
    //neu khoang cach nho nhat ma minh tim duoc < int((x-4800)*float(1.1)) : move to temporary position --> sut bong (move to ballposition) 
    
    while(1){
        cout <<position<<endl;
        
        buffer = network.get_message(position); //input: position, output: buffer
        
        
        cout <<"=========Begin========"<<endl;
        cout<<buffer<<endl;
        cout <<"**********End*********"<<endl;
        
        sleep(2);
        
        //cout<<"test:  "<<a.split_line(buffer,'\n').at(0)<<endl;
        
        vector<string> lines = parser.split_line(buffer,'\n');
        
        cout<<"bao nhiu bien: "<<lines.size()<<endl;
       
        int n = lines.size();
        Player p;
        for(int i=0 ; i < n; i++){
            p = parser.parse_player(lines.at(i));
            //cout<<"line thu " << i << ":" << p.get_position() <<endl;
            if(p.get_name() == "B"){
                B.set_xy(p.get_x(),p.get_y());
                cout<<"toa do Ball: " << B.get_position() <<endl;
            }
            if(p.get_name() == "R1"){
                R1.set_xy(p.get_x(),p.get_y());
                cout<<"toa do R1: " << R1.get_position() <<endl;
            }
            if(p.get_name() == "R2"){
                R2.set_xy(p.get_x(),p.get_y());
                cout<<"toa do R2: " << R2.get_position() <<endl;
            }
            if(p.get_name() == "R3"){
                R3.set_xy(p.get_x(),p.get_y());
                cout<<"toa do R3: " << R3.get_position() <<endl;
            }
            if(p.get_name() == "R4"){
                R4.set_xy(p.get_x(),p.get_y());
                cout<<"toa do R4: " << R4.get_position() <<endl;
            }
            if(p.get_name() == "R5"){
                R5.set_xy(p.get_x(),p.get_y());
                cout<<"toa do R5: " << R5.get_position() <<endl;
            }
        }
        
	
    }
    network.close_connect();
}
