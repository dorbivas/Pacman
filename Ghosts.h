#pragma once
#include "Pacman.h"

#define INITAL_GHOST_X 15
#define INITAL_GHOST_Y 2
class Ghosts
{

private:
    Position pos;
    int direction;

public:
    //constructors
    Ghosts() {
        direction = STAY;
        pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
    }
    ~Ghosts();

    Position get_position();
    void set_position(Position pos);
    void set_position(int x, int y);
    int get_direction();
    void set_direction(int direction);
   // Position get_pacman_position(Pacman pacman);
    void set_direction_near();

};
