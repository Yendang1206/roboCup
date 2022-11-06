#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

vector<string> split2(string &s, char delim){
    vector<string> output;
    stringstream ss(s);
    string sub;
    
    while(getline(ss, sub, delim)){
        output.push_back(sub);
    }
    return output;
}

class Player{

    protected:

	string name;
	int x;
	int y;

    public:

	Player();
	
	Player(string name, int x, int y);
	
	
	void set_x(int x);
        void set_y(int y);
        void set_xy(int x, int y);
        void set_linedata(string line);
        
      
        double distance(int x, int y);
        double distance(Player another);

        int get_x(void);
        int get_y(void);
        int get_xy(void);
	
	string get_name(void);
	string get_position(void);
	
	
	~Player();
};
