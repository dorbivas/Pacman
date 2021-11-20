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
    Ghosts();
    ~Ghosts();

    Position get_position();
    void set_position(Position pos);
    void set_position(int x, int y);
    int get_direction();
    void set_direction(int direction);
    Position move_ghost();
    void set_direction_near();//TODO

};
