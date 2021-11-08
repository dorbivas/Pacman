#include <iostream>
#include <random>
#include "Position.h"
using namespace std;

class Packman
{

private:
    int souls;
    int direction;
    Position pos;

public:
    Packman();
    //Packman(int s,int drection);
    //Packman() { this->souls = 3; this->direction = 0; };
    int get_souls();
    int get_direction();
    void set_souls(int souls);
    void set_direction(int direction);
    Position get_position();
    void set_position(Position pos);

    //Packman();//set_xy(33, 33); //TODO recalebrait/
};
