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
    
    Player R3("3", 3, 10);
    Player R4("4", 0, 0);

    cout << R3.get_x() << endl;
    cout << R3.get_y() << endl;
    cout <<"Khoang cach R3 "<<R3.distance(R4)<<endl;
    cout << R3.get_name()<< endl;
    //cout <<"Khoang cach R4 "<<R4.distance(R4)<<endl;
    cout <<"================"<<endl;
    
    string ip = "localhost";
    string port = "10000"; //let's talk on http port

    std::unique_ptr<Socket> sock(new Socket(AF_INET,SOCK_STREAM,0));
    sock->connect(ip, port);

    //sock->socket_write("3000,1000\n");

    //int seconds = 10;

    vector<Socket> reads(1);

    reads[0] = *sock;
    string buffer;

    /*
    if(sock->select(&reads, NULL, NULL, seconds) < 1){
	sock->socket_write("100,100\n");
    }else{
        string buffer;
        sock->socket_read(buffer, 1024);
        cout << buffer << endl;
    }
    */
    vector<string> data;
    vector<string> lines;
    vector<string> linedata;
    vector<string> dataContent;
    //vector<string> DesTem;
    //vector<string> DesBall;
    
    string position = "4,0,1000\n"; //toa do ban dau cua R3, gui message thi can '\n"
    string label;
    string line;
    string labelname;
    string labelposition;
    //string Destination = "4800,1650";
    string Temporary =  "x1, y1";
	
	
    while(1){
	cout << position << endl; 
	sock->socket_write(position);
	sock->socket_read(buffer, 1024); //doc toa do dc gui ve trong buffer
	sleep(3);
	cout <<"================"<<endl;
	cout << buffer << endl; //in ra toa do dc gui ve
	cout <<"================"<<endl;
	//data = split(buffer, ':');
	lines = split(buffer, '\n'); //chia ra tung dong
	line = lines.at(0); 
	//linedata = split(lines.at(0), ':'); 
	cout<<"dong line [0]: "<<line<<endl;
	
	label = split(line, ':'); 
	labelname = label.at(0);
	cout<<"label: "<<labelname<<endl;//in ra "B"
	
	
	/*
	label = split(lines.at(0), '\n'); //dong line dau tien 
	labelname = label.at(0); //in ra B, R1, R2
	cout<<"label: "<<labelname<<endl;//in ra "B"
	labelposition = label.at(1);
	linedata = split(labelposition, ',');
	cout<<"line data vi tri 0: "<<linedata.at(0)<<endl;
	
	cout<<"line data vi tri 1: "<<linedata.at(1)<<endl;
	
	*/
	//cout << data.at(0) << endl;	
	//cout << data.at(1) << endl;
	
	/*
	
	int x = std::stoi(linedata.at(0)); //in ra toa do x cua Ball
	int y = std::stoi(linedata.at(1)); //in ra toa do y cua Ball
	cout << "x: " << x << " " << "y: " << y << endl;
	string Ballposition = std::to_string(x) + "," + std::to_string(y) + "\n";
	
	
	//toa do DB de tinh toa do Tem
	//DesBall.at(0) = (x-4800)*float(1.1);
	//DesBall.at(1) = (y-1650)*float(1.1);
	
	//toa do Temporary make
	string x1 = std::to_string(4800 + int((x-4800)*float(1.1)));
	string y1 = std::to_string(1650 + int((y-1650)*float(1.1)));
	
	//cout<<"toa do x cua Tem"<<Temporary.at(0)<<"toa do y cua Tem"<<Temporary.at(1)<<endl; -> phai day vao ham string thi moi cout dc	
	string Temporary = x1 + "," + y1 + "\n";
	//position = Temporary;
	cout<<"toa do tem: "<<Temporary<<endl;
	sock->socket_write(Temporary);
	//sock->socket_read(buffer, 1024);
	linedata = split(buffer, ',');
	sleep(3); 
	
	*/

	/*string A = "2160,1650\n";
	sock->socket_write(A);
	sock->socket_read(buffer, 1024);
	cout<<"line 63: toa do diem A"<<A<<endl;
	cout << buffer << endl;
	data = split(buffer, ',');
	sleep(3);*/
	
	
	/*
	//string Ballposition;
	sock->socket_write(Ballposition);
	//sock->socket_read(buffer, 1024);
	cout<<"line 70: toa do diem Ball"<<Ballposition<<endl;
	cout << buffer << endl;
	linedata = split(buffer, ',');
	
	*/
	
	//cout << data.at(0) << endl;	
	//cout << data.at(1) << endl;

	/* get integers */

	//int x = std::stoi(data.at(0));
	//int y = std::stoi(data.at(1));

	//cout << "x: " << x << " " << "y: " << y << endl;
	
	//position = std::to_string(x) + "," + std::to_string(y) + "\n";
	//cout << position << endl; 
	sleep(3);
    }
    sock->close();
}
