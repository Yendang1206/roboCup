#include "parser.hpp"

Parser::Parser(){

}

Player Parser::parse_player(string position_line){

    char label[100];
    char xchar[100];
    char ychar[100];
    
    sscanf(position_line.c_str(), "%[^:]:%[^,],%s", label, xchar, ychar);
   
    int x = stoi(xchar);
    int y = stoi(ychar);
    
    Player B(label,x,y);
    return B;
}


vector<string> Parser::split_line(string &s, char delim){
    vector<string> output;
    stringstream ss(s);
    string sub;
    
    while(getline(ss, sub, delim)){
        output.push_back(sub);
    }
    return output;
}

Parser::~Parser(){

}
