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
    
    
   
    Player B("b",2400,1650);
    Player R1("1",0,0);
    Player R2("2",0,0);
    Player R3("3",0,0);
    Player R4("4",0,0);
    Player R5("5",0,1650);
    
    Player Tem("t",0,0);
    
    
    //cout<<R3.get_x()<<endl;
    //cout<<R3.get_y()<<endl;
    //cout<<"Khoang cach R3: "<<R3.distance(R4)<<endl;
    //cout<<"Robot number "<<R3.get_name()<<endl;
    //cout<<"--------------------"<<endl;
    
    
    
   
     
    
   // double soccer_list[4]={R1.distance(Tem), R2.distance(Tem), R3.distance(Tem), R4.distance(Tem)};
    
    
    string position = R5.get_position(); //toa do Goal
    
    //string Temporary = "3,x1,y1";
    
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
        
        Tem.set_x(4800 + int((B.get_x()-4800)*float(1.05)));
        Tem.set_y(1650 + int((B.get_y()-1650)*float(1.05)));
    
        cout<<"toa do tem_x,y: "<<Tem.get_position()<<endl;
        
        cout<<"R1 vs Tem: "<<R1.distance(Tem)<<endl;
        cout<<"R2 vs Tem: "<<R2.distance(Tem)<<endl;
        cout<<"R3 vs Tem: "<<R3.distance(Tem)<<endl;
        cout<<"R4 vs Tem: "<<R4.distance(Tem)<<endl;
        
        
        double soccer_list[]={R1.distance(Tem), R2.distance(Tem), R3.distance(Tem), R4.distance(Tem)};
        //cout << "list of soccer: "<<soccer_list[0]<<endl;
        double min = 9000.0;
        int min_index;   
        for (int i=0;i<4;i++){
           if(soccer_list[i] < min){
              min = soccer_list[i];
              min_index = i+1;
           }
	}   
	cout<<"min dis: "<<min<<endl;
	cout<<"min index: "<<min_index<<endl;
	
	if(min<=3){
	   Player new_position(to_string(min_index),B.get_x(),B.get_y());
	   position = new_position.get_position();
	
	}
	else{
	   Player new_position(to_string(min_index),Tem.get_x(),Tem.get_y());
	   position = new_position.get_position();
	}
	
    }
    network.close_connect();
}
