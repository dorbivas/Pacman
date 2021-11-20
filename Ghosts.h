#pragma once
#include "Pacman.h"

#define INITAL_GHOST_X 17
#define INITAL_GHOST_Y 6
class Ghosts
{

private:
    Position pos;
    int direction;

public:
    //constructors
    Ghosts(){
        direction = rand() % 4;
        pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
    }
    ~Ghosts() {};

    Position get_position() { return pos; };
    void set_position(Position Pos) { this->pos = Pos; };
    void set_position(int x, int y) { pos.set_xy(x, y); };
    int get_direction() { return direction; }
    void set_direction() { direction = rand() % 4; };
    Position move_ghost();
    //void set_direction_near();//TODO

};
