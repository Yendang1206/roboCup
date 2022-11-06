
#include "player.hpp"

using namespace std;

class State{
    private:
        Player R3();
        
        /*
        Player r1();
        Player r2();
        Player r3();
        Player r4();
        
        */
        
    public:
        State();
        
        void set_state(string data); //input string
        string get_position(void);

        
        ~State();
};
