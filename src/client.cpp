#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <unistd.h>
#include "socket.hpp"
#include "player.hpp"


using namespace std;

vector<string> split(string &s, char delim){
    vector<string> output;
    stringstream ss(s);
    string sub;
    
    while(getline(ss, sub, delim)){
        output.push_back(sub);
    }
    return output;
}



int main(int argc, char *argv[]){
   
    Player B("b",0,0);
    Player R1("1",0,0);
    Player R2("2",0,0);
    Player R3("3",0,0);
    Player R4("4",0,0);
    Player R5("5",0,0);
    
    cout<<R3.get_x()<<endl;
    cout<<R3.get_y()<<endl;
    cout<<"Khoang cach R3: "<<R3.distance(R4)<<endl;
    cout<<"Robot number "<<R3.get_name()<<endl;
    cout<<"--------------------"<<endl;
    

    string ip= "localhost";
    string port = "10000";
    unique_ptr<Socket> sock(new Socket(AF_INET,SOCK_STREAM,0));
    sock->connect(ip, port);
    vector<Socket> reads(1);
    reads[0] = *sock;
    string buffer;
    
    vector<string> data;
    vector<string> lines;
    vector<string> linedata;
    vector<string> dataContent;
    
    string position = "3,0,1650\n"; //toa do Goal
    string newPosition = "3,x_p,y_p\n"; //toa do moi cua R3
    string line;
    string label;
    string labelposition;
    string Temporary = "3,x1,y1";
    string place;
    
   
    
    
    
    //doc toa do cua cac robot, ball -> gan nhat -> chay toi toa do temporary -> sut bong
    //if khong gan ball -> tiep tuc di chuyen tip toi temporary -> sut bong
    
    //toa do ball -> tinh toa do temporary -> tim khoang cach cua con robot nao gan nhat vs toa do temporary
    //neu khoang cach nho nhat ma minh tim duoc < int((x-4800)*float(1.1)) : move to temporary position --> sut bong (move to ballposition) 
    
    while(1){
        cout <<position<<endl;
        sock->socket_write(position);
        //sock->socket_write(newPosition);
        sock->socket_read(buffer,1024);
        sleep(0.02);
        
        
        cout <<"=========Begin========"<<endl;
        cout<<buffer<<endl;
        cout <<"**********End*********"<<endl;
        
        //TODO: position = ?
        
        //tao class PlayerState playstate(); 
        
        //2 functions: - playstate.set_state(buffer)
        //             position = playstate.get_position()
        
        //field.set_state(buffer); //input la buffer, output: void
        
        
        data = split(buffer, ':');
        
        
        //cout<<data.at(0)<<endl; //vi la vector nen k cout dc 
        //cout<<data.at(1)<<endl; //day ve gia tri string nhu dong 66 de cout
        
        label = data.at(0);
        cout<<"label: "<<label<<endl;
        
        labelposition = data.at(1);
        data = split(labelposition, ',');
        
        int x = stoi(data.at(0)); //toa do x_Ball
	int y = stoi(data.at(1)); //toa do y_Ball
        B.set_xy(x,y);
        
	cout <<"Toa do x,y cua Ball: "<<B.get_position()<< endl;
	string Ballposition = R3.get_name() + "," + to_string(x) + "," + to_string(y) + "\n";
	
	//toa do Temporary
	string x1 = to_string(4800 + int((x-4800)*float(1.1)));
	string y1 = to_string(1650 + int((y-1650)*float(1.1)));
	
	string Temporary = R3.get_name() + "," + x1 + "," + y1 + "\n";
        cout<<"toa do temporary: "<<Temporary<<endl;
	sock->socket_write(Temporary);	
	sock->socket_read(buffer,1024);
	sleep(0.02); 
	
	//lay toa do R3 va toa do Ball, tinh khoang cach R3 vs Ball
	
	sock->socket_write(Ballposition);
	cout<<"toa do diem Ball: "<<Ballposition<<endl;
	//cout<<"Toa do updated: " << buffer << endl;
	
	sleep(3);
	
	data = split(buffer, ':');
	
	//toa do moi
	place = data.at(0);
        cout<<"Vi tri moi: "<<place<<endl;
        
	newPosition = data.at(1);
        data = split(newPosition, ',');
        
        int x_p = stoi(data.at(0)); //toa do moi
        int y_p = stoi(data.at(1)); //toa do moi
	
	cout <<"Toa do moi: "<< "new x: " << x_p << " " << "new y: " << y_p << endl;
	
	string newPosition = R3.get_name() + "," + to_string(x_p) + "," + to_string(y_p) + "\n";
	
	Temporary = newPosition;
	
    }
    sock->close();


}
