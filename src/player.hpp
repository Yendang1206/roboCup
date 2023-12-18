#ifndef PLAYER
#define PLAYER
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <sstream>
using namespace std;

class Player{
    private:
	string name;
	int x;
	int y;
    public:
	Player();
	Player(string name, int x, int y);
	vector<string> split(string &s, char delim);
	
	void set_x(int x);
        void set_y(int y);
        void set_xy(int x, int y);
        void set_linedata(string line);
        void update_attack_position(Player Ball);
        void update_defense_position(Player Ball);
        void update_prepare_position(Player Ball);
      
        double distance(int x, int y);
        double distance(Player another);
        double protection(int x, int y, double t, double a);// x vs y: toa do cua robot; t: time; a: gia toc
        bool check_in_line(Player Tem, Player Ball);

        int get_x(void);
        int get_y(void);
        int get_xy(void);
        
	string get_name(void);
	string get_position(void);
	
	~Player();
};
#endif
