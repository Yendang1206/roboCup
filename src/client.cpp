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
    Parser parser;
   
    Player B("b",2400,1650); //Ball's position
    Player R1("1",3600,825);
    Player R2("2",1200,825);
    Player R3("3",3600,2475);
    Player R4("4",1200,825);
    Player R5("5",0,1650);
    Player Tem("t",0,0); //Temporary's position
  
    string position = R1.get_position() + R2.get_position() + R3.get_position() + R4.get_position() + R5.get_position();
        
    while(1){
        
        buffer = network.get_message(position);        
        cout<<buffer<<endl;
        sleep(0.02);
        
        vector<string> lines = parser.split_line(buffer,'\n');
        cout<<"Size of buffer: "<<lines.size()<<endl;
       
        int n = lines.size();
        Player p;
       
        for(int i=0 ; i < n; i++){
            p = parser.parse_player(lines.at(i));

            if(p.get_name() == "B"){
                B.set_xy(p.get_x(),p.get_y());
                cout<<"Ball's position: " << B.get_position() <<endl;
            }
            else if(p.get_name() == "R1"){
                R1.set_xy(p.get_x(),p.get_y());
                cout<<"R1's position: " << R1.get_position() <<endl;
            }
            else if(p.get_name() == "R2"){
                R2.set_xy(p.get_x(),p.get_y());
                cout<<"R2's position: " << R2.get_position() <<endl;
            }
            else if(p.get_name() == "R3"){
                R3.set_xy(p.get_x(),p.get_y());
                cout<<"R3's position: " << R3.get_position() <<endl;
            }
            else if(p.get_name() == "R4"){
                R4.set_xy(p.get_x(),p.get_y());
                cout<<"R4's position: " << R4.get_position() <<endl;
            }
            else if(p.get_name() == "R5"){
                R5.set_xy(p.get_x(),p.get_y());
                cout<<"R5's position: " << R5.get_position() <<endl;
            }
        }
        
        /*Calculate Coordinate of Temporary*/
        Tem.set_x(4800 + int((B.get_x()-4800)*1.1));
        Tem.set_y(1650 + int((B.get_y()-1650)*1.1));
        cout<<"Temporary's position: " <<Tem.get_position()<<endl;
        
        /*GoalKeeper's position: R5 will move around half-circle to prevent the ball
           P(0,1650)
           B: Ball position
           C: a target point that R5 will move to C 
        */
        int PBx = B.get_x();  
        int PBy = B.get_y() - 1650;
        int PCx = int(330*PBx / sqrt(PBx*PBx + PBy*PBy));
        int PCy = int(330*PBy / sqrt(PBx*PBx + PBy*PBy));
        
        R5.set_x(PCx);
        R5.set_y(PCy + 1650);
        
        /*Making a strategy for 4 robots: 
           R1 and R2: attack
           R3 and R4: defense 
        */
        if(B.get_y() >= 1650){
           R2.update_attack_position(B);
	   R3.update_defense_position(B);
           R1.update_prepare_position(B);
           R4.update_prepare_position(B);
        }
        else{
           R1.update_attack_position(B);
	   R4.update_defense_position(B);
	   R2.update_prepare_position(B);
           R3.update_prepare_position(B);
        }
	
	position = R1.get_position() + R2.get_position() + R3.get_position() + R4.get_position() + R5.get_position();
	
	cout<<"Robot's position is updated: " <<position<<endl;

    }
    network.close_connect();
}
