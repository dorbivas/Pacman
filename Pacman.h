#include <iostream>
#include <random>
#include "Position.h"
using namespace std;

class Pacman
{

private:
    int souls;
    int direction;
    Position pos;
    int score;

public:
    //constructors
    Pacman();
    ~Pacman();
    //Pacman(int s,int drection);
    //Pacman() { this->souls = 3; this->direction = 0; };

    int get_souls();
    void set_souls(int souls);
    int get_direction();
    void set_direction(int direction);
    Position get_position();
    void set_position(Position pos);

    void decrease_soul();

    //Pacman();//set_xy(33, 33); //TODO recalebrait/
};
