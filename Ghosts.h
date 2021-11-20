#pragma once
#include "Pacman.h"

#define INITAL_GHOST_X 17
#define INITAL_GHOST_Y 6
class Ghosts
{

private:
    Position pos;
    int direction;
    int steps;//steps counter

public:
    //constructors
    Ghosts(){
        steps = 0;
        direction = rand() % 4;
        pos.set_xy(INITAL_GHOST_X, INITAL_GHOST_Y);
    }
    ~Ghosts() {};

    Position get_position() { return pos; }
    int get_step() { return steps; }
    void set_position(Position Pos) { this->pos = Pos; }
    void set_position(int x, int y) { pos.set_xy(x, y); }
    int get_direction() { return direction; }

    void set_direction() {
        if (steps == 20) { steps = 0; direction = rand() % 4; }
        else { steps++; }
    }
    
    void rotate_direction() {//TODO STATIC
        if (direction == 3) { direction = 0; }
        else { direction++; }
    }
        
    Position move_ghost();

};
