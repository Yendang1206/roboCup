#ifndef PARSER
#define PARSER
#include <iostream>
#include <stdio.h>
#include "network.hpp"
#include <string>
#include <sstream>
#include "player.hpp"
using namespace std;

class Parser{
public:
    Parser();
    Player parse_player(string position_line);
    vector<string> split_line(string &s, char delim);
    ~Parser();
};
#endif





